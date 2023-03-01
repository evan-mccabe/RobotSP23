#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <math.h>

//Include constants
#include <constants.h>

//Include object port declarations
#include <declarations.h>

//Include movement functions
#include <movement.h>

int main(void)
{   
    float x, y; //for touch screen

    //Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);

    LCD.WriteLine("Shaft Encoder Exploration Test");
    LCD.WriteLine("Touch the screen");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed


    //Navigate up the ramp and to the boarding pass kiosk

    right_turn(45);
    move_forward(3);
    right_turn(10);
    move_forward(2);
    left_turn(10);
    ramp(30);
    left_turn(45);
    move_forward(13);
    right_turn(45);

    //Move forward until microswitches are both pressed
    moveUntil();
    

    Sleep(2.0); //Wait for counts to stabilize



    return 0;
}

