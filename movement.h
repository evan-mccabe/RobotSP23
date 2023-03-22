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

    int lever = 0;

    arm.SetDegree(45);
    
    //RPS.GetCorrectLever();

    if (lever == 0){


        arm.SetDegree(10);
        move_backward(1);

        arm.SetDegree(0);
        Sleep(5.5);
        arm.SetDegree(10);
        

    }
    else if(lever == 1){

        move_backward(2);

        //Add servo logic

    }
    else if(lever == 2){

        move_backward(3);

        //Add servo logic

    }


}