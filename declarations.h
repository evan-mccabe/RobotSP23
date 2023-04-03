//Object port declarations


//Shaft encoders
DigitalEncoder right_encoder(FEHIO::P1_1);
DigitalEncoder left_encoder(FEHIO::P1_2);

//Drive motors
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);

//Bump switches
DigitalInputPin rfmicro(FEHIO::P1_4);
DigitalInputPin lfmicro(FEHIO::P1_5);

//Cds cell
AnalogInputPin cds(FEHIO::P1_0);

//Optosensors
AnalogInputPin ropt(FEHIO::P0_0);
AnalogInputPin mopt(FEHIO::P0_1);
AnalogInputPin lopt(FEHIO::P0_2);

//Arm
FEHServo arm(FEHServo::Servo0);


//Suitcase

FEHServo suitcase(FEHServo::Servo1);

//min is 500

//max is 2500

