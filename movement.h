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

void moveUntil(){


    while ((lfmicro.Value()||rfmicro.Value())){

        right_motor.SetPercent(rmp);
        left_motor.SetPercent(lmp);

    }

    right_motor.SetPercent(0);
    left_motor.SetPercent(0);
    
}