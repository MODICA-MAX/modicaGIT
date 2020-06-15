//Program to test the inductive sensors and their sensitivity
//test cycle will have the platforms rasining and lowering from top to bottom.
//Pogram by Max Cerami on this day of our Lord lil' Bub: 3/11/3030-1010

//declare variables

boolean firstRun = false; // variable for doing 1 loop at begining of each program.
int cycleCounter = 0; //so we know how many up and downs the system goes
boolean Direction1Down = false; 
boolean Direction2Down = true;
int leftrightcycles = 0; //for cycle testing

void setup() {
  // declaring pins for Motor Control
pinMode(0, OUTPUT); //motor 1 INPUT A
pinMode(1, OUTPUT); //motor 1 INPUT B
pinMode(2, OUTPUT); //motor 1 ENABLE
pinMode(3, OUTPUT); //Motor 2 INPUT A
pinMode(4, OUTPUT); //motor 2 INPUT B
pinMode(5, OUTPUT); //Motor 2 ENABLE
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);

 // pins for sensor inputs
pinMode(14, INPUT);  //Side 1 High Sensor
pinMode(15, INPUT);  //Side 1 Low Sensor
pinMode(16, INPUT);  //Side 2 High Sensor
pinMode(17, INPUT);  //Side 2 Low Sensor
// pins for button
  //E-Stop
pinMode(18, INPUT); //oh fuck button

//disable everything on motors
      digitalWrite(0,HIGH); 
      digitalWrite(1,HIGH);
      digitalWrite(2,HIGH);
      digitalWrite(3,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);



}

void loop() {
  //while magazine is feeding upward, raise the current bay platen at low speed while upper optical sensor is unblocked
  //when current bay platen reaches top prox sensor, wait for a duration or until reset input, then lower the platen at the LoweringSpeed until it reaches the bay's bottom prox sensor



//start off the motors from current location in opposite directions. default is side 2 goes down and side 1 goes up.

//debugging
//Serial.println("motor 1 High Sensor");
//Serial.println(digitalRead(14));
//Serial.println("motor 1 LOW Sensor");
//Serial.println(digitalRead(15));
//Serial.println("motor 2 High Sensor");
//Serial.println(digitalRead(16));
//Serial.println("motor 2 LOW Sensor");
//Serial.println(digitalRead(17));


if (firstRun==false) {
  //delay(3000); //startup pause
  //send motor 1 UP
  digitalWrite(2, LOW); //Turn motor 1 ENABLE ON. motor should turn on and bay 1 platen should rise
  //send motor 2 DOWN
  digitalWrite(5, LOW); //Motor 2 ENABLE ON. motor should turn and bay 2 platen should lower
  //change boolean to true
  firstRun == true;
}

//Sensor Logic 
  //Motor 1 moving up, hits sensor then moves down
      //Sensor 1 Higher is triggered
          if (digitalRead(14) == LOW){
            digitalWrite(0, HIGH); //Turn motor 1 INPUT A OFF
              //for the cycle counter
              if (Direction1Down ==false){
                leftrightcycles=leftrightcycles+1; //increment cycle counter
                Serial.print("the amount of cycles is: ");
                Serial.println(leftrightcycles);
                }
            Direction1Down=true; 
          }
        
  //Motor 1 moving down, hits sensor then moves up
     //Sensor 1 Lower is triggered
            if (digitalRead(15) == LOW){
            digitalWrite(1, HIGH); //Turn motor 1 INPUT B OFF
            Direction1Down=false;
          }
//moving the motors outside the if.
          if (Direction1Down == true){
            digitalWrite(1, LOW); //Turn motor 1 INPUT B ON
          }
          if (Direction1Down == false){
            digitalWrite(0, LOW); //Turn motor 1 INPUT A ON
          }
          
  //Motor 2 moving up, hits sensor then moves down
     //Sensor 2 Higher is triggered
          if (digitalRead(16) == LOW){
            digitalWrite(3, HIGH); //Turn motor 2 INPUT A OFF
            Direction2Down=true;
          }
  //Motor 2 moving down, hits sensor then moves up
     //Sensor 2 Higher is triggered
          if (digitalRead(17) == LOW){
            digitalWrite(4, HIGH); //Turn motor 2 INPUT B OFF
            Direction2Down=false;
          }
//moving the motors outside the if.
          if (Direction2Down == true){
            digitalWrite(4, LOW); //Turn motor 2 INPUT B ON
          }
          if (Direction2Down == false){
            digitalWrite(3, LOW); //Turn motor 2 INPUT A ON
          }
//ESTOP
    //if (digitalRead(18) == LOW){
       // digitalWrite(0,HIGH); 
       // digitalWrite(1,HIGH);
        //digitalWrite(2,HIGH);
       // digitalWrite(3,HIGH);
       // digitalWrite(4,HIGH);
       // digitalWrite(5,HIGH);
        //digitalWrite(6,HIGH);
        //digitalWrite(7,HIGH);
        
    }
