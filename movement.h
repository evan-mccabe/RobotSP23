#include <declarations.h>
#include <constants.h>


void move_forward(float inches)
{
    //Calculate number of motor counts for the distance that needs to be travelled
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
    //Calculate number of motor counts for the distance that needs to be travelled
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
    //Calculate number of motor counts for the distance that needs to be travelled
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

    //Find necessary counts to rotate x degrees
    int counts = degrees*degreesCount;

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

    //Find necessary counts to rotate x degrees
    int counts = degrees*degreesCount;

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

void moveUntil(){

    float startTime = TimeNow();

    bool keep = true;

    //move until both microswitches are pressed and time hasnt reached 5 seconds
    while ((lfmicro.Value()||rfmicro.Value())&&(keep)){

        

        right_motor.SetPercent(rmp);
        left_motor.SetPercent(lmp);

        //Timeout after 5 seconds
        if(TimeNow()-startTime>5){
            keep = false;
        }


    }

    //turn motors off
    right_motor.SetPercent(0);
    left_motor.SetPercent(0);
    
}

void moveUntilOne(){

    float startTime = TimeNow();

    bool keep = true;

    //move until both microswitches are pressed
    while ((lfmicro.Value() && rfmicro.Value())&&keep){

        right_motor.SetPercent(rmp);
        left_motor.SetPercent(lmp);

        //Timeout after 5 seconds
        if(TimeNow()-startTime>5){
            keep = false;
        }


    }

    //turn motors off
    right_motor.SetPercent(0);
    left_motor.SetPercent(0);
    
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

    //Wait .5 seconds until checking to see if the robot is off of the line, exit the loop if so
    if((TimeNow()-startTime)>=.5){
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

    //If the light is red
    if ((cds.Value())<1.1){
        color = Red;
        LCD.Clear();
        LCD.SetBackgroundColor(RED);

        //If the light is blue
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

        //Move forward for 2 seconds to press button
        while((TimeNow()-t)<2){
            left_motor.SetPercent(lmp);
            right_motor.SetPercent(rmp);
        }
        left_motor.SetPercent(0);
        right_motor.SetPercent(0);

        
       
    }
    //If light is red
    if (c == Red){

        LCD.WriteLine("Red");
        move_backward(18);
        right_turn(45);

        float t = TimeNow();

        //Move forward for 3 seconds to press button
        while((TimeNow()-t)<3){
            left_motor.SetPercent(lmp);
            right_motor.SetPercent(rmp);
        }
        
        left_motor.SetPercent(0);
        right_motor.SetPercent(0);
        
    }

    
    


}

void fuel(){

    

    arm.SetDegree(45);

    //Get the correct lever from rps
    int lever = RPS.GetCorrectLever();

    //If Jet A
    if (lever == 0){

        left_turn(1);
        arm.SetDegree(20);
        Sleep(.5);
        move_backward(2.5);
        Sleep(.5);
        arm.SetDegree(20); 

        //Flip lever down and wait 
        arm.SetDegree(1); 
        Sleep(5.5);

        //Flip lever back down
        arm.SetDegree(25);
        Sleep(.5);
        move_forward(2);
        arm.SetDegree(120);

        //Go back to initial position
        move_forward(.5);
        

    }//If Jet A1
    else if(lever == 1){

        left_turn(1);
        move_backward(4.5);
        Sleep(.5);
        arm.SetDegree(20);
        Sleep(.5);
        move_backward(2);
        Sleep(.5);
        arm.SetDegree(1);
        Sleep(5.5);
        arm.SetDegree(1);
        arm.SetDegree(25); 
        Sleep(.5);
        move_forward(2);
        arm.SetDegree(120);

        //Go back to initial position
        move_forward(4.5);

    }//If Jet B
    else {

        left_turn(1);
        move_backward(8);
        Sleep(.5);
        arm.SetDegree(20); 
        Sleep(.5);
        move_backward(2.25);
        Sleep(.5);
        arm.SetDegree(20); 
        arm.SetDegree(1); 
        Sleep(5.5);
        arm.SetDegree(25);
        Sleep(.5);
        move_forward(2);
        arm.SetDegree(120);

        //Go back to initial position
        move_forward(8.25);
    }


}

void passport(){

    //Manipulate passport lever
    arm.SetDegree(179);
    Sleep(1.0);
    arm.SetDegree(60);
    Sleep(1.0);
    arm.SetDegree(175);



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
    int power = PULSE_POWER*2;
    if (orientation == MINUS)
    {
        power = -PULSE_POWER*2;
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
    int power = PULSE_POWER*2;
    if (orientation == MINUS)
    {
        power = -PULSE_POWER*2;
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
void check_heading(float heading, float tolerance)
{

    bool c = true;

    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while (c && (RPS.Heading()>-1.5)&&(RPS.Heading() < (heading - tolerance) || (RPS.Heading() > (heading + tolerance))))
    {
        LCD.WriteLine(RPS.Heading());
        float state1 = RPS.Heading();

        if (RPS.Heading() > heading)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_counterclockwise(-1.5*PULSE_POWER,PULSE_TIME);
        }
        else if (RPS.Heading() < heading)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_counterclockwise(1.5*PULSE_POWER,PULSE_TIME);
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
