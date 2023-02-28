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

    right_turn(45);
    move_forward(3);
    right_turn(10);
    move_forward(2);
    left_turn(10);
    ramp(30);
    left_turn(45);
    move_forward(13);
    right_turn(45);

    while ((lfmicro.Value()||rfmicro.Value())){

        right_motor.SetPercent(rmp);
        left_motor.SetPercent(lmp);
    }



    right_motor.SetPercent(0);
    left_motor.SetPercent(0);

    

    Sleep(2.0); //Wait for counts to stabilize



    return 0;
}

