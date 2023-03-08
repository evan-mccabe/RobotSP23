#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <math.h>

//Include movement functions
#include <movement.h>


int main(void)
{   
    float x, y; //for touch screen

    //Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);



    LCD.WriteLine("Touch the screen to start");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed

    /*
    while(1){

        LCD.WriteLine("Right");
        LCD.WriteLine(ropt.Value());
        LCD.WriteLine("Middle");
        LCD.WriteLine(mopt.Value());
        LCD.WriteLine("Left");
        LCD.WriteLine(lopt.Value());
        LCD.WriteLine("CDS");
        LCD.WriteLine(cds.Value());


        Sleep(.5);

        LCD.Clear();
    }
    */


    while(cds.Value()>3){
    }

    //Navigate up the ramp and to the boarding pass kiosk
    
    right_turn(45);
    move_forward(4);
    right_turn(10);
    move_forward(4);
    left_turn(10);
    ramp(23);
    lineFollow();
    right_motor.SetPercent(0);
    left_motor.SetPercent(0);
    left_turn(15);
    move_forward(1);
    int color = detect();
    
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

    Sleep(2.0); //Wait for counts to stabilize



    return 0;
}

