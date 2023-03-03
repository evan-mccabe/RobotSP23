#include <declarations.h>
#include <constants.h>


void move_forward(float inches)
{
    int counts = inches*inchesCount;
    
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(rmp);
    left_motor.SetPercent(lmp);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void move_backward(float inches)
{
    int counts = inches*inchesCount;
    
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(-rmp);
    left_motor.SetPercent(-lmp);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while(abs((left_encoder.Counts() + right_encoder.Counts()))/ 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void ramp(float inches)
{
    int counts = inches*inchesCount;
    
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(rmp*2);
    left_motor.SetPercent(lmp*2);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}


void left_turn(float degrees){

    int counts = degrees*3.2;

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(rmp);
    left_motor.SetPercent(-1*lmp);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while(((left_encoder.Counts()) + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();


}

void right_turn(int degrees){

    int counts = degrees*3.2;

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(-1*rmp);
    left_motor.SetPercent(lmp);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while(((left_encoder.Counts()) + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();


}

int moveUntil(){

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();


    while ((lfmicro.Value()||rfmicro.Value())){

        right_motor.SetPercent(rmp);
        left_motor.SetPercent(lmp);

    }

    right_motor.SetPercent(0);
    left_motor.SetPercent(0);

    return ((abs(left_encoder.Counts()+right_encoder.Counts()))/2.0)/inchesCount;
    
}

void lineFollow(){


//Declare states for state machine

enum LineStates {

MIDDLE,

RIGHT,

LEFT

};

int state = MIDDLE; // Set the initial state

//Follow the line while the cds cell isnt reading anything
while (cds.Value()<3) {

switch(state) {

// If I am in the middle of the line...

case MIDDLE:

// Set motor powers for driving straight

right_motor.SetPercent(rmp);
left_motor.SetPercent(lmp);

/* Drive */

if (ropt.Value()>2.0) {

state = RIGHT; // update a new state

}

/* Code for if left sensor is on the line */

if (lopt.Value()>2.0) {

state = LEFT; // update a new state

}

break;

// If the right sensor is on the line...

case RIGHT:

// Set motor powers for right turn

left_motor.SetPercent(25);
right_motor.SetPercent(0);


/* Drive */

if(ropt.Value()<2.0) {

/* update a new state */

state=MIDDLE;

}

break;

// If the left sensor is on the line...


case LEFT:

/* Mirror operation of RIGHT state */

left_motor.SetPercent(0);
right_motor.SetPercent(25);

/* Drive */

if(lopt.Value()<2.0) {

/* update a new state */

state=MIDDLE;

}

break;

default: // Error. Something is very wrong.

break;


}

Sleep(3);


}

right_motor.SetPercent(0);
left_motor.SetPercent(0);

}

int detect(){

    int color;

    if (cds.Value()<1){
        color = Red;
    }else{
        color = Blue;
    }

    return color;


}

void ticket(int color){

    if (color == Blue){
        move_backward(12);
       
    }
    if (color == Red){
        move_backward(23);
    }
    
    right_turn(45);
    moveUntil();


}