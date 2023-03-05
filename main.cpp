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

    while(cds.Value()>2){
    }

    //Navigate up the ramp and to the boarding pass kiosk
    
    right_turn(45);
    move_forward(4);
    right_turn(10);
    move_forward(4);
    left_turn(10);
    ramp(23);
    lineFollow();

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

