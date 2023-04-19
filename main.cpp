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

/*
TESTING CODE
*/

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


    //Position to back up to fuel levers
    move_forward(17.5);
    right_turn(130);
    check_heading(90,1);
    arm.SetDegree(45);
    move_forward(.5);

    //Back up and flip correct fuel lever
    fuel();
    
    //Square off against right wall
    check_heading(90,3);

    moveUntil(7);

    move_backward(.5);
    left_turn(85);
    check_heading(180,1);
    ramp(26);

    //Navigate up the ramp and complete suitcase task
    check_heading(180,1);
    //check_y(49.5,PLUS);
    left_turn(87);
    check_heading(270,1);
    move_forward(15);
    check_x(13,MINUS);
    left_turn(88);

    //Square off against suitcase bin
    moveUntilOne();
    
    //Drop suitcase
    suitcase.SetDegree(50);
    Sleep(.5);
    suitcase.SetDegree(178);
    move_backward(5);
    left_turn(165);

    //Changed from 168
    check_heading(170,1);

    //Follow line to complete fuel lever task
    lineFollow();

    left_turn(10);
    move_forward(2);

    int color = detect();
    left_turn(20);

    //Square off against tower

    moveUntil(0);
    
    //Press correct ticket button
 
    ticket(color);


    //Passport task

    move_backward(3);
    check_y(61,PLUS);
    left_turn(85);
    arm.SetDegree(175);
    check_heading(270,1);


    if(color==Blue){

        //Changed from 6
        move_backward(7);
    }else{
        
        //Changed from 2
        move_backward(3);
    }

    check_x(24,MINUS);

    passport();

    move_forward(5);
    
    //Go to the final button

    right_turn(85);
    check_heading(180,1);

    lmp=50;
    rmp=50;
    move_backward(11);
    lmp=25;
    rmp=25;

    right_turn(85);

    moveUntil(6);
    move_backward(.5);
    right_turn(85);

    //Speed up
    rmp*=2;
    lmp*=2;

    move_forward(20);
    right_turn(40);
    move_forward(12);
    left_turn(77);
    move_forward(20);
    
    Sleep(2.0); //Wait for counts to stabilize

    return 0;
}

