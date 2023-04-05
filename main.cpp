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

    RPS.InitializeTouchMenu();

    //Set min and max for each servo
    suitcase.SetMin(500);
    suitcase.SetMax(2500);
    arm.SetMin(500);
    arm.SetMax(2500);

    LCD.WriteLine("Touch the screen to start");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed


    //Wait for start light
    LCD.Clear();
    LCD.WriteLine("Waiting for start light");
    while(cds.Value()>3){
    }

    LCD.Clear();
    LCD.WriteLine("Started run");


    move_forward(17.5);
    right_turn(135);
    check_heading(90,1);
    arm.SetDegree(45);
    move_forward(.5);

    fuel();
    
    //Reset arm
    arm.SetDegree(120);
    moveUntil();
    move_backward(.5);
    left_turn(90);
    check_heading(180,1);
    ramp(26);

    check_heading(180,1);
    check_y(49.5,PLUS);
    left_turn(90);
    check_heading(270,1);
    move_forward(15);
    check_x(13,MINUS);
    left_turn(88);
    check_y(42,MINUS);
    moveUntilOne();
    Sleep(1.0);
    suitcase.SetDegree(50);
    Sleep(1.0);
    suitcase.SetDegree(180);
    Sleep(1.0);
    move_backward(5);
    left_turn(160);
    check_heading(160,1);
    move_forward(2);
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

    //Passport task

    //move_backward(??)
    check_y(61,PLUS);
    left_turn(90);
    arm.SetDegree(175);
    check_heading(270,1);

    if(color==Blue){
        //change these
        move_backward(5);
    }else{
        //change these
        move_backward(1);
    }
    check_x(24,MINUS);
    Sleep(1.0);
    arm.SetDegree(60);
    Sleep(1.0);
    arm.SetDegree(175);
    move_forward(5);

    //Go to the final button

    Sleep(2.0); //Wait for counts to stabilize

    return 0;
}

