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

    LCD.WriteLine("Touch the screen to start");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed

    //Set min and max for each servo
    suitcase.SetMin(500);
    suitcase.SetMax(2500);

    arm.SetMin(500);
    arm.SetMax(2500);

    //Sleep(5.0);

    //suitcase.SetDegree(50);

    /*
    while (true){
    LCD.Clear();
    LCD.WriteLine("X:");
    LCD.WriteLine(RPS.X());
    LCD.WriteLine("Y:");
    LCD.WriteLine(RPS.Y());

    Sleep(1.0);


    }

    */

    while(cds.Value()>3){
    }

    right_turn(45);
    move_forward(4);
    right_turn(10);
    move_forward(4);
    left_turn(12);
    check_heading(180);
    ramp(26);
    check_heading(180);
    check_y(49.5,PLUS);
    left_turn(90);
    check_heading(270);
    move_forward(15);
    check_x(12,MINUS);
    left_turn(90);
    check_heading(0);
    check_y(42,MINUS);
    moveUntilOne();

    Sleep(2.0);
    suitcase.SetDegree(50);
    suitcase.SetDegree(90);

    move_backward(4);
    right_turn(90);
    check_heading(270);
    move_forward(3);
    right_turn(90);
    check_heading(180);
    move_backward(10);
    right_turn(90);
    check_heading(90);
    move_forward(10);
    right_turn(45);
    check_heading(45);
    move_forward(15);




    /*
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
    check_heading(180);
    move_forward(4.5);
    check_y(61,PLUS);
    left_turn(90);
    arm.SetDegree(175);
    check_heading(270);
    move_backward(5);
    check_x(24,MINUS);
    Sleep(1.0);
    arm.SetDegree(60);
    Sleep(1.0);
    arm.SetDegree(175);
    move_forward(5);
    */



   /*Fuel checkpoint
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

