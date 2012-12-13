/*
    model.h - (c) Michael Weber, Jr. (2012)

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

#ifndef MODEL_H
#define MODEL_H

#include <stdlib.h>
#include <QtGui>
using namespace std;

// This is a car as defined in the model
struct Car
{
    public:
        // When the car is first created it is initialized to a random spot in the road
        Car(int, int, int, double);
        void update();      // This goes through the steps of moving the car
        void reset();       // When a car goes off the road it loops back to the start

        int desiredSpeed;   // This is the desired velocity of the car
        int speed;          // This is the car's current velocity
        int lane;           // This is the lane the car is in
        int cell;           // This is the cell the car is in
        double brake;       // Propability that the car will decrease its velocity by one
};

// Model sets up the road and makes sure all the cars play well together
class Model
{
    public:
        Model();
        virtual ~Model();

        Car ***cells;               // This is the road way, if the cell is not occupied it will be null
        Car **cars;                 // This holds all the cars
        int numberOfCells;          // Number of cells in the roadway
        int numberOfLanes;          // Number of lanes in the roadway
        int numberOfCars;           // Number of cars in the simulation
        int numberofTimeSteps;      // Number of timesteps for the simulation

        int max_vel;                // The max velocity that any car can have
        double brake;               // The probabilty of a car braking for each car
        double trucks;              // Percentage of trucks on the road
        int voff;                   // This determines how much headway we need to move back right

        int currentTick;

        void init();
        void tick();

        static Model *instance;

        QVector<double> lane1_use;      // This is the number of cars in lane 1 at each tick
        QVector<double> lane2_use;      // This is the number of cars in lane 2 at each tick
        QVector<double> avg_speed;      // The average speed of the vehicles
        QVector<double> time_count;     // We need to keep track of the tick count for the graph to wrok

        void dump();

    private:
};

void csv(const char* filename, QVector<double> &time, QVector<double> &lane1, QVector<double> &lane2, QVector<double> &speed);

#endif // MODEL_H
