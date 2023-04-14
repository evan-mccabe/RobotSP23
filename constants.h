//Constants

//# of counts for 1 inch of movement
float inchesCount = 40.49; 

//# of counts for 1 degree of turn
float degreesCount = 3.2;

//Left motor percent
int lmp = 25;

//Right motor percent
int rmp = 25;

//Colors for cds cell selection

enum colors {

Red,

Blue

};

enum levers{
a,
a1,
b

};


////RPS

// Number of points of interest (i.e. A, B, C, D)
#define NUM_POINTS_OF_INTEREST 4

// RPS Delay time
#define RPS_WAIT_TIME_IN_SEC 0.35

// Shaft encoding counts for CrayolaBots
#define COUNTS_PER_INCH 40.5
#define COUNTS_PER_DEGREE 2.48

/* Defines for how long each pulse should be and at what motor power. 
These value will normally be small, but you should play around with the values to find what works best */
#define PULSE_TIME .1
#define PULSE_POWER 10

// Define for the motor power while driving (not pulsing)
#define POWER 25

#define HEADING_TOLERANCE 2

/* Direction along axis which robot is traveling
Examples:
    - if robot is traveling to the upper level, that is a PLUS as the y-coordinate is increasing
    - if robot is traveling to the lower level, that is a MINUS as the y-coordinate is decreasing
*/
#define PLUS 0
#define MINUS 1