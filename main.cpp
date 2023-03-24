#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHServo.h>
#include <FEHBattery.h>
#include <math.h>

//Include movement functions
#include <movement.h>


int main(void)
{   
    float x, y; //for touch screen

    //Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);

    //RPS.InitializeTouchMenu();

    LCD.WriteLine("Touch the screen to start");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed

    //Set min and max for each servo
    suitcase.SetMin(500);
    suitcase.SetMax(2500);

    arm.SetMin(550);
    arm.SetMax(2500);

    arm.SetDegree(179);
    /*
    while(cds.Value()>3){
    }
    
    //Passport checkpoint
    right_turn(45);
    move_forward(4);
    right_turn(10);
    move_forward(4);
    left_turn(12);
    ramp(26);
    check_heading(180);
    left_turn(45);
    move_forward(13);
    right_turn(45);
    moveUntil();
    move_backward(2);
    left_turn(90);
    arm.SetDegree(179);
    check_heading(270);
    move_backward(5.5);
    arm.SetDegree(90);
    Sleep(1.0);
    arm.SetDegree(179);
    move_forward(5);

    */

    





    /* Fuel lever code
    move_forward(17.5);
    right_turn(135);
    check_heading(90);
    arm.SetDegree(45);
    move_forward(.5);

    //2.25
    //6
    //9.5

    fuel();
    */




    
    /*
    //Navigate up the ramp and to the boarding pass kiosk
    

    right_turn(45);
    move_forward(4);
    right_turn(10);
    move_forward(4);
    left_turn(12);
    ramp(24);

    lineFollow();
    right_motor.SetPercent(0);
    left_motor.SetPercent(0);
    left_turn(15);
    move_forward(2);

    int color = detect();
    left_turn(10);

    //Square off against tower
    moveUntil();
    

    //Press correct ticket button
    ticket(color);

    move_backward(16);
    right_turn(90);

    moveUntil();
    move_backward(.5);
    right_turn(90);

    move_forward(28);

    lmp=100;
    rmp=100;
    right_turn(360);

    rmp=25;
    lmp=25;

    */

    Sleep(2.0); //Wait for counts to stabilize

    return 0;
}

