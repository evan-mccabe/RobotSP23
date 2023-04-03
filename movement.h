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

    //move until both microswitches are pressed
    while ((lfmicro.Value()||rfmicro.Value())){

        right_motor.SetPercent(rmp);
        left_motor.SetPercent(lmp);


    }

    Sleep(1);

    //turn motors off
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

bool cont = true;

float startTime = TimeNow();

//Follow the line while there is one
while (cont) {

    switch(state) {

    // If I am in the middle of the line...

    case MIDDLE:

    // Set motor powers for driving straight

    right_motor.SetPercent(rmp);
    left_motor.SetPercent(lmp);

    /* Drive */

    if (ropt.Value()<2.7) {

    state = RIGHT; // update a new state
    LCD.WriteLine("RIGHT");

    }

    /* Code for if left sensor is on the line */

    if (lopt.Value()<2.7) {

    state = LEFT; // update a new state
    LCD.WriteLine("LEFT");


    }

    break;

    // If the right sensor is on the line...

    case RIGHT:

    // Set motor powers for right turn

    left_motor.SetPercent(25);
    right_motor.SetPercent(0);


    /* Drive */

    if(mopt.Value()<2.7) {

    /* update a new state */

    state=MIDDLE;
    LCD.WriteLine("MIDDLE");

    }

    break;

    // If the left sensor is on the line...


    case LEFT:

    /* Mirror operation of RIGHT state */

    left_motor.SetPercent(0);
    right_motor.SetPercent(25);

    /* Drive */

    if(mopt.Value()<2.7) {

    /* update a new state */

    state=MIDDLE;
    LCD.WriteLine("MIDDLE");

    }

    break;

    default: // Error. Something is very wrong.

    break;



    }

    Sleep(3);

    if((TimeNow()-startTime)>=5){
    if ((lopt.Value()>=2.7)&&(mopt.Value()>=2.7)&&(ropt.Value()>=2.7)){

        cont = false;
        LCD.WriteLine("End of line");

    }
    }


    }

right_motor.SetPercent(0);
left_motor.SetPercent(0);

}

int detect(){

    int color;

    float value = 0;

    Sleep(2.0);

    LCD.WriteLine(cds.Value());
    if ((cds.Value())<1.1){
        color = Red;
        LCD.Clear();
        LCD.SetBackgroundColor(RED);
        
    }else{
        color = Blue;
        LCD.Clear();
        LCD.SetBackgroundColor(BLUE);
        
        
    }
    move_forward(.1);


    
    
    return color;


}

void ticket(int c){

    LCD.Clear();

    //If light is blue
    if (c == Blue){

        LCD.WriteLine("Blue");
        move_backward(11);
        right_turn(45);
        float t = TimeNow();

        //Move forward for 3 seconds to press button
        while((TimeNow()-t)<3){
            left_motor.SetPercent(25);
            right_motor.SetPercent(25);
        }
        left_motor.SetPercent(0);
        right_motor.SetPercent(0);

        
       
    }
    //If light is red
    if (c == Red){

        LCD.WriteLine("Red");
        move_backward(17);
        right_turn(45);

        float t = TimeNow();

        //Move forward for 5 seconds to press button
        while((TimeNow()-t)<5){
            left_motor.SetPercent(25);
            right_motor.SetPercent(25);
        }
        
        left_motor.SetPercent(0);
        right_motor.SetPercent(0);
        
    }

    
    


}

void fuel(){

    

    arm.SetDegree(45);
    
    int lever = RPS.GetCorrectLever();

    if (lever == 0){
        //Move back 2
        arm.SetDegree(20);
        Sleep(1.0);
        move_backward(2);
        Sleep(1.0);
        arm.SetDegree(20); 
        arm.SetDegree(1); 
        Sleep(5.5);
        arm.SetDegree(25); 
        

    }
    else if(lever == 1){


        //Move back 5.75

        move_backward(4.5);
        Sleep(1.0);
        arm.SetDegree(20);
        Sleep(1.0);
        move_backward(1.25);
        Sleep(1.0);
        arm.SetDegree(1);
        Sleep(5.5);
        arm.SetDegree(1);
        arm.SetDegree(25); 

    }
    else if(lever == 2){

        //Move back 9

        left_turn(1);
        move_backward(8);
        Sleep(1.0);
        arm.SetDegree(20); 
        Sleep(1.0);
        move_backward(1);
        Sleep(1.0);
        arm.SetDegree(20); 
        arm.SetDegree(1); 
        Sleep(5.5);
        arm.SetDegree(25); 
    }


}

void passport(){

    arm.SetDegree(179);
    //move_backward(10);
    Sleep(5.0);
    arm.SetDegree(85);
    arm.SetDegree(179);
    Sleep(.5);
    move_forward(10);



}

//RPS
/*
 * Pulse counterclockwise a short distance using time
 */
void pulse_counterclockwise(int percent, float seconds)
{
    // Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-percent);

    // Wait for the correct number of seconds
    Sleep(seconds);

    // Turn off motors
    right_motor.Stop();
    left_motor.Stop();

}

/*
 * Pulse forward a short distance using time
 */
void pulse_forward(int percent, float seconds)
{
    // Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    // Wait for the correct number of seconds
    Sleep(seconds);

    // Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

/*
 * Use RPS to move to the desired x_coordinate based on the orientation of the QR code
 */
void check_x(float x_coordinate, int orientation)
{
    // Determine the direction of the motors based on the orientation of the QR code
    int power = PULSE_POWER;
    if (orientation == MINUS)
    {
        power = -PULSE_POWER;
    }

    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while ( (RPS.X()>-1.5) && (RPS.X() < x_coordinate - 1 || RPS.X() > x_coordinate + 1))
    {
        if (RPS.X() > x_coordinate)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_forward(-power, PULSE_TIME);
        }
        else if (RPS.X() < x_coordinate)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_forward(power, PULSE_TIME);
        }
        Sleep(RPS_WAIT_TIME_IN_SEC);

        if(RPS.X()<0){
            Sleep(RPS_WAIT_TIME_IN_SEC);
        }

        LCD.WriteLine(RPS.X());
    }
}

/*
 * Use RPS to move to the desired y_coordinate based on the orientation of the QR code
 */
void check_y(float y_coordinate, int orientation)
{
    // Determine the direction of the motors based on the orientation of the QR code
    int power = PULSE_POWER;
    if (orientation == MINUS)
    {
        power = -PULSE_POWER;
    }

    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while ( (RPS.Y()>-1.5) &&(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1))
    {
        if (RPS.Y() > y_coordinate)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_forward(-power, PULSE_TIME);
        }
        else if (RPS.Y() < y_coordinate)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_forward(power, PULSE_TIME);
        }
        Sleep(RPS_WAIT_TIME_IN_SEC);

        if(RPS.Y()<0){
            Sleep(RPS_WAIT_TIME_IN_SEC);
        }

        LCD.WriteLine(RPS.Y());
    }
}

/*
 * Use RPS to move to the desired heading
 */
void check_heading(float heading)
{
    // You will need to fill out this one yourself and take into account
    // checking for proper RPS data and the edge conditions
    //(when you want the robot to go to 0 degrees or close to 0 degrees)

    /*
        SUGGESTED ALGORITHM:
        1. Check the current orientation of the QR code and the desired orientation of the QR code
        2. Check if the robot is within the desired threshold for the heading based on the orientation
        3. Pulse in the correct direction based on the orientation
    */

    // Determine the direction of the motors based on the orientation of the QR code

    bool c = true;

    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while (c && (RPS.Heading()>-1.5)&&(RPS.Heading() < (heading - 3) || (RPS.Heading() > (heading + 3))))
    {
        LCD.WriteLine(RPS.Heading());
        float state1 = RPS.Heading();

        if (RPS.Heading() > heading)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_counterclockwise(-PULSE_POWER,PULSE_TIME);
        }
        else if (RPS.Heading() < heading)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_counterclockwise(PULSE_POWER,PULSE_TIME);
        }
        Sleep(RPS_WAIT_TIME_IN_SEC);

        float state2 = RPS.Heading();

        if((state1>0) && (state2>0)){

        if(abs(state1-state2)>100){

            if(state1>200){
                pulse_counterclockwise(-PULSE_POWER/2.0,PULSE_TIME);
                c = false;
            }
            else if(state2>200){
                pulse_counterclockwise(PULSE_POWER/2.0,PULSE_TIME);
                c = false;
            }

        }
        }

        Sleep(RPS_WAIT_TIME_IN_SEC);

        if(RPS.Heading()<0){
            Sleep(RPS_WAIT_TIME_IN_SEC);
        }

        

    }
    }


int moveUntilOne(){

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //move until both microswitches are pressed
    while ((lfmicro.Value() && rfmicro.Value())){

        right_motor.SetPercent(rmp);
        left_motor.SetPercent(lmp);


    }

    Sleep(1);

    //turn motors off
    right_motor.SetPercent(0);
    left_motor.SetPercent(0);


    return ((abs(left_encoder.Counts()+right_encoder.Counts()))/2.0)/inchesCount;
    
}