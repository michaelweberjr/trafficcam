/*
    model.cpp - (c) Michael Weber, Jr. (2012)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "model.h"

Car::Car(int vel, int lane, int cell, double brake)
{
    this->cell = cell;
    this->lane = lane;
    this->brake = brake;

    desiredSpeed = vel;
    speed = desiredSpeed;
}

void Car::update()
{
    if(cell >= Model::instance->numberOfCells) return;

    int headway = 0;
    bool changing_lanes = false;
    for(int i = cell+1; i < Model::instance->numberOfCells; i++)
    {
        if(Model::instance->cells[i][lane] != NULL) break;
        headway++;
    }
    if(cell+headway+1 < Model::instance->numberOfCells && headway <= speed)
    {
        if(headway < speed && lane == 0)
        {
            changing_lanes = true;
            for(int j = cell + speed; j > cell-Model::instance->max_vel; j--)
            {
                // if we would go off the road then passing is still valid and no checks for cars need to be made
                if(j >= Model::instance->numberOfCells) continue;
                // This checks if our passing would move into a car and thus would be worse
                if(j >= cell && Model::instance->cells[j][1] != NULL)
                {
                    changing_lanes = false;
                    break;
                }
                // This checks to see if a car would then move into us
                if(j >= 0 && Model::instance->cells[j][1] != NULL && Model::instance->cells[j][1]->speed+j >= cell)
                {
                    changing_lanes = false;
                    break;
                }
            }
        }
        if(!changing_lanes) speed = headway;
    }
    else if(speed < desiredSpeed)
    {
        speed++;
    }
    else if(speed == desiredSpeed && lane == 1)
    {
        headway = 0;
        for(int i = cell; i < Model::instance->numberOfCells; i++)
        {
            if(Model::instance->cells[i][0] != NULL) break;
            headway++;
        }
        if(headway > speed+Model::instance->voff)
        {
            changing_lanes = true;
            for(int i = cell; i >= cell - Model::instance->max_vel; i--)
            {
                if(i >= 0 && Model::instance->cells[i][0] != NULL && Model::instance->cells[i][0]->speed+i >= cell)
                {
                    changing_lanes = false;
                    break;
                }
            }
        }
    }

    if(speed > 0 && rand() % 100 < brake * 100) speed--;

    Model::instance->cells[cell][lane] = NULL;
    cell += speed;
    if(changing_lanes) lane = lane == 1 ? 0 : 1;
    if(cell < Model::instance->numberOfCells) Model::instance->cells[cell][lane] = this;
}

void Car::reset()
{
    if(Model::instance->cells[0][0] == NULL)
    {
        desiredSpeed = Model::instance->max_vel;
        desiredSpeed -= rand() % 100 < Model::instance->trucks * 100 ?  2 : 0;
        speed = desiredSpeed;
        cell = 0;
        lane = 0;
        Model::instance->cells[0][0] = this;
    }
    else if(Model::instance->cells[0][1] == NULL)
    {
        desiredSpeed = Model::instance->max_vel;
        desiredSpeed -= rand() % 100 < Model::instance->trucks * 100 ?  2 : 0;
        speed = desiredSpeed;
        cell = 0;
        lane = 1;
        Model::instance->cells[0][1] = this;
    }
}

Model *Model::instance = NULL;

Model::Model()
{
    instance = this;
    srand(2288);
}

void Model::init()
{
    currentTick = 0;

    cells = new Car**[numberOfCells];
    for(int i = 0; i < numberOfCells; i++)
    {
        cells[i] = new Car*[numberOfLanes];
        for(int j = 0; j < numberOfLanes; j++)
            cells[i][j] = NULL;
    }

    cars = new Car*[numberOfCars];

    lane1_use.resize(numberofTimeSteps);
    lane2_use.resize(numberofTimeSteps);
    avg_speed.resize(numberofTimeSteps);
    time_count.resize(numberofTimeSteps);

    // If the number of cars is less then the number of cells then put all cars into the same lane
    if(numberOfCells > numberOfCars)
    {
        for(int i = 0; i < numberOfCars; i++)
        {
            // First find a valid spot
            int cell = rand() % (numberOfCells - i);
            int l = 0;
            for(int j = 0; j < cell; j++, l++)
            {
                if(cells[l][0] != NULL) l++;
            }
            if(cells[l][0] != NULL) l++;

            // Now set the desired speed limit
            int vel = max_vel;
            if(rand() % 100 < trucks * 100) vel -= 2;

            // Now create the car
            cars[i] = new Car(vel, 0, l, brake);
            cells[l][0] = cars[i];
        }
    }
    else // otherwise random spread amongst the lanes
    {
        int totalCells = numberOfLanes*numberOfCells;
        for(int i = 0; i < numberOfCars; i++)
        {
            // First find a valid spot
            int cell = rand() % (totalCells - i);
            int lane;
            int l = 0;
            for(int j = 0; j < cell; j++, l++)
            {
                lane = l < totalCells / 2 ? 0 : 1;
                if(cells[l < totalCells / 2 ? l : l - numberOfCells][lane] != NULL) l++;
            }
            if(cells[l < totalCells / 2 ? l : l - numberOfCells][lane] != NULL) l++;
            l = l < totalCells / 2 ? l : l - numberOfCells;
            lane = l < totalCells / 2 ? 0 : 1;

            // Now set the desired speed limit
            int vel = max_vel;
            if(rand() % 100 < trucks * 100) vel -= 2;

            // Now create the car
            cars[i] = new Car(vel, lane, l, brake);
            cells[l][0] = cars[i];
        }
    }

    /*FILE* file = fopen("cars.csv", "w");
    for(int i = 0; i < numberOfCars; i ++)
        fprintf(file, "%d,%d,%d,%d\n", i, cars[i]->lane, cars[i]->cell, cars[i]->speed);
    fclose(file);*/
}

void Model::tick()
{
    if(currentTick % 10000 == 0) printf("%d\n", currentTick);
    if(currentTick++ < numberofTimeSteps)
    {
        // We update cars by going in order from first to last and left to right
        for(int i = numberOfCells - 1; i >= 0; i--)
        {
            for(int j = numberOfLanes - 1; j >= 0; j--)
            {
                if(cells[i][j] != NULL)
                    cells[i][j]->update();
            }
        }

        // now check for finished cars
        for(int i = 0; i < numberOfCars; i++)
        {
            if(cars[i]->cell >= numberOfCells)
                cars[i]->reset();
        }

        /*if(currentTick == 1)
        {
            FILE* file = fopen("cars2.csv", "w");
                for(int i = 0; i < numberOfCars; i ++)
                    fprintf(file, "%d,%d,%d,%d\n", i, cars[i]->lane, cars[i]->cell, cars[i]->speed);
                fclose(file);
        }*/

        // now that everything is updated we set the results
        int lane1 = 0, lane2 = 0;
        int speed = 0;
        for(int i = 0; i < numberOfCells; i++)
        {
            if(cells[i][0] != NULL)
            {
                lane1++;
                speed += cells[i][0]->speed;
            }
        }
        for(int i = 0; i < numberOfCells; i++)
        {
            if(cells[i][1] != NULL)
            {
                lane2++;
                speed += cells[i][1]->speed;
            }
        }
        lane1_use[currentTick-1] = lane1;
        lane2_use[currentTick-1] = lane2;
        avg_speed[currentTick-1] = (double)speed/(lane1+lane2);
        time_count[currentTick-1] = currentTick;
    }
}

void csv(const char * filename, QVector<double> &time, QVector<double> &lane1, QVector<double> &lane2, QVector<double> &speed)
{
    FILE* file = fopen(filename, "w");
    fprintf(file, "Time Step,Lane 1,Lane 2,Avg Speed\n");
    for(int i = 0; i < time.size(); i++)
    {
        fprintf(file, "%lf,%lf,%lf,%lf\n", time[i], lane1[i], lane2[i], speed[i]);
    }
    fclose(file);
}

Model::~Model()
{
    //delete lane1_use;
    //delete lane2_use;
}

void Model::dump()
{
    printf("Model Dump\n");
    printf("Number of Lanes: %d\n", numberOfLanes);
    printf("Number of Cells: %d\n", numberOfCells);
    printf("Number of Cars: %d\n", numberOfCars);
    printf("Number of Time Steps: %d\n", numberofTimeSteps);
    printf("Max Velocity: %d\n", max_vel);
    printf("Braking probility: %lf\n", brake);
    printf("Percentage of Trucks: %lf\n", trucks);
    printf("Vehicle Offset: %d\n", voff);
}
