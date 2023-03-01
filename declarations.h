//Object port declarations
DigitalEncoder right_encoder(FEHIO::P3_0);
DigitalEncoder left_encoder(FEHIO::P3_1);
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);
DigitalInputPin rfmicro(FEHIO::P2_0);
DigitalInputPin lfmicro(FEHIO::P2_1);
AnalogInputPin cds(FEHIO::P1_0);