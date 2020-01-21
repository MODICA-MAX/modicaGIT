//This is a program to create a PIDloop to drive the Z motor of the PlotterBOT-
//up and down acording to the value of the laser height reading.  

//Include Relevant libraries:
#include <PID_v1.h>

//Initialize Globals Variables
int LaserPin = A0;         // select the input pin for the Laser analog out
double LaserValue = 0;     // variable to store the value coming from the Laser
double LaserSetValue=0;    //Var for setpoint of laser
double LaserSetLow=0;    //Var for setpoint of laser
double LaserSetHigh=0;    //Var for setpoint of laser
double Margin = 10;      //keeps the sensor from hunting
//stuff for height is set switch*******
int switchPin = 2;         // digital in for switch for height-set on
int ledPin = 13;           // this will light up the led on the arduino board when switch is active
int switchState = 0;       // variable for reading switch state
int InitializedSwitchState = 0;   // variable for reading the last switch state
int Zstep;
// stuff for motor control*************

int smDirectionPin = 8;      //Direction pin
int smStepPin = 10;          //Stepper pin
int smEnablePin = 9;       //Motor enable pin

// Tuning parameters for PID***********
//float Kp=0;                // Initial Proportional Gain
//float Ki=10;               // Initial Integral Gain
//float Kd=0;                // Initial Differential Gain 

//double Setpoint, Input, Output; //These are just variables for storingvalues
//PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
                                              // This sets up our PDID Loop
                                              //Input is our PV
                                              //Output is our u(t)
                                              //Setpoint is our SP
//const int sampleRate = 1; // Variable that determines how fast our PID loop runs
// Communication setup
//const long serialPing = 500; //This determines how often we ping our loop
// Serial pingback interval in milliseconds
//unsigned long now = 0; //This variable is used to keep track of time
// placehodler for current timestamp
//unsigned long lastMessage = 0; //This keeps track of when our loop last spoke to serial
// last message timestamp.
//Initialize



//*********************************************************************************

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(switchPin, INPUT);
  
  //start the serial
  Serial.begin(9600);
 
  //Sets all pin to output; the microcontroller will send them(the pins) bits, it will not expect to receive any bits from thiese pins.*/
  pinMode(smDirectionPin, OUTPUT);
  pinMode(smStepPin, OUTPUT);
  pinMode(smEnablePin, OUTPUT);
  }
 

//*********************************************************************************

void loop() {
  //lets everything boot
  //delay(5000);

//Read the Value on the Laser
  LaserValue = analogRead(LaserPin);
//Scale Value to get actual height in mm

//logic for making sure booting arduino doesn't cause any issues if the switch was left on.
//Create a conditional for first time startup
//if (InitializedSwitchState = 1){ 
  //delay(1000);
  //Serial.println(InitializedSwitchState);
  //InitializedSwitchState = digitalRead(switchPin);

  // read the state of the Switch value:
     switchState = digitalRead(switchPin);
       
    if (switchState==HIGH){
      //Turn on Arduino LED showing height is set.
        digitalWrite(ledPin, HIGH);
        //Serial.println(switchState);
        Serial.println("SETPOINT");
        Serial.println(LaserSetValue);
        Serial.println("WhereweAt?");
        Serial.println(LaserValue);
     
        
      //run active PID control
        digitalWrite(smEnablePin, LOW); //Enables the motor, so it can be a badass bitch
      //define setpoint
        if (LaserSetValue==0){
          LaserSetValue=LaserValue;
          //define margin of acceptable error
          LaserSetHigh = LaserSetValue + Margin;
          LaserSetLow = LaserSetValue - Margin;
        }
      //compare and make calculation
        if (LaserValue<LaserSetLow){
            //move the Z axis UP
            Zstep = abs(LaserSetValue-LaserValue)/4;
             rotate(-Zstep, 0.1); //The motor rotates 800 steps clockwise with a speed of 0.1 (slow)
             //delay(20);
        }
        else if (LaserValue>LaserSetHigh){
          //move the Z axis UP
             Zstep = abs(LaserSetValue-LaserValue)/4;
             rotate(Zstep, 0.1); //The motor rotates 800 steps clockwise with a speed of 0.1 (slow)
             //delay(20);
        }
}
    else {
        //turn off Arduino LED showing that height is not set
        digitalWrite(ledPin, LOW);
        Serial.println("Level Not Set");
        digitalWrite(smEnablePin, HIGH); //Disbales the motor, so it can rest untill it is called uppond
        LaserSetValue=0;
        Serial.println("WhereweAt?");
        Serial.println(LaserValue);
        delay(500);
        
}

}

/*The rotate function turns the stepper motor. Tt accepts two arguments: 'steps' and 'speed'*/
void rotate(int steps, float speed){
  digitalWrite(smEnablePin, LOW); //Enabling the motor, so it will move when asked to
 
  /*This section looks at the 'steps' argument and stores 'HIGH' in the 'direction' variable if */
  /*'steps' contains a positive number and 'LOW' if it contains a negative.*/
  int direction;
 
  if (steps > 0){
    direction = HIGH;
  }else{
    direction = LOW;
  }
 
  speed = 1/speed * 70; //Calculating speed
  steps = abs(steps); //Stores the absolute value of the content in 'steps' back into the 'steps' variable
 
  digitalWrite(smDirectionPin, direction); //Writes the direction (from our if statement above), to the EasyDriver DIR pin
 
  /*Steppin'*/
  for (int i = 0; i < steps; i++){
    digitalWrite(smStepPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(smStepPin, LOW);
    delayMicroseconds(speed);
  }
}
