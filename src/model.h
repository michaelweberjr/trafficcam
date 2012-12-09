#ifndef MODEL_H
#define MODEL_H

// This is a car as defined in the model
struct Car
{
    public:
        // When the car is first created it is initialized to a random spot in the road
        void init(int vel, int lane, int cell);
        void update();      // This goes through the steps of moving the car

        int vel;            // This is the desired velocity of the car
        int current_vel;    // This is the car's current velocity
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

        Car **cells;                // This is the road way, if the cell is not occupied it will be null
        Car *cars;                  // This holds all the cars
        int numberOfCells;          // Number of cells in the roadway
        int numberOfLanes;          // Number of lanes in the roadway
        int numberOfCars;           // Number of cars in the simulation
        int numberofTimeSteps;      // Number of timesteps for the simulation

        int max_vel;                // The max velocity that any car can have
        double brake;               // The probabilty of a car braking for each car
        double trucks;              // Percentage of trucks on the road

        int ** results;             // The results of each timestep is the number of cars in each lane

    private:
};

#endif // MODEL_H
