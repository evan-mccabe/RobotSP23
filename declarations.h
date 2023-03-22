//Object port declarations


//Shaft encoders
DigitalEncoder right_encoder(FEHIO::P3_0);
DigitalEncoder left_encoder(FEHIO::P3_1);

//Drive motors
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);

//Bump switches
DigitalInputPin rfmicro(FEHIO::P2_0);
DigitalInputPin lfmicro(FEHIO::P2_1);

//Cds cell
AnalogInputPin cds(FEHIO::P1_0);

//Optosensors
AnalogInputPin ropt(FEHIO::P0_0);
AnalogInputPin lopt(FEHIO::P0_2);
AnalogInputPin mopt(FEHIO::P0_1);

//Arm
FEHServo arm(FEHServo::Servo0);


//Suitcase

FEHServo suitcase(FEHServo::Servo1);

//min is 500

//max is 2500