//Program to test the system when rotato is included
//test cycle will have the platforms rasining and lowering from top to bottom.
//Pogram by Max Cerami on this day of our Lord lil' Bub: 4/29/2020

//declare variables

boolean firstRunComplete = false; // variable for doing 1 loop at begining of each program.
boolean waitbuttonstart = false; //variable to wait for user to choose which stack to start with.
boolean side1atbottom = false; //variable for stating whether platten 1 is at bottom
boolean side2atbottom = false; //variable for stating whether platten 2 is at bottom
boolean side1attop = false; //variable for stating whether platten 1 is at top
boolean side2attop = false; //variable for stating whether platten 2 is at top

int MoveMotor1 = 0; //using to halt motor (0), move up (1), move down (2)
int MoveMotor2 = 0;
int indexup = 0; //var used to give the badgebot 3 tries at indexing the level of the badges up before it does not ratchet them up any more incase it masses on first try

int side1Button =0; //side 1 stack ready to feed (1) or not ready (0)
int side2Button =0; //side 2 stack ready to feed (1) or not ready (0)

void setup() {
  // declaring pins for Motor Control
pinMode(0, OUTPUT); //motor 1 INPUT A
pinMode(1, OUTPUT); //motor 1 INPUT B
pinMode(2, OUTPUT); //motor 1 and 2 ENABLE
pinMode(3, OUTPUT); //Motor 2 INPUT A
pinMode(4, OUTPUT); //motor 2 INPUT B
pinMode(5, OUTPUT); //Rotate Rotato CW
pinMode(6, OUTPUT); //Rotate Rotato CCW
pinMode(7, OUTPUT); //Suckers on!

 // pins for sensor inputs 
pinMode(14, INPUT);  //Side 1 High Sensor
pinMode(15, INPUT);  //Side 1 Low Sensor
pinMode(16, INPUT);  //Side 2 High Sensor
pinMode(17, INPUT);  //Side 2 Low Sensor
pinMode(18, INPUT);  //throughbeam Sensor
// pins for button
pinMode(19, INPUT);  //Retract Platforms
pinMode(20, INPUT);  //Side 1 Ready
pinMode(21, INPUT);  //Side 2 Ready

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

//********************************************************************************************
//debugging
//Serial.println(F("motor 1"));
//Serial.println(MoveMotor1);
//Serial.println(F("motor 2"));
//Serial.println(MoveMotor2);
//
//Serial.println(F("firstRunComplete"));
//Serial.println(firstRunComplete);
//Serial.println(F("waitbuttonstart"));
//Serial.println(waitbuttonstart);
//
//Serial.println(F("side1atbottom"));
//Serial.println(side1atbottom);
//Serial.println(F("side2atbottom"));
//Serial.println(side2atbottom);
//Serial.println(F("side1attop"));
//Serial.println(side1attop);
//Serial.println(F("side2attop"));
//Serial.println(side2attop);
//
//Serial.println(F("throughbeam"));
//Serial.println(digitalRead(18));
//
//Serial.println(F("side1button"));
//Serial.println(side1Button);
//Serial.println(F("side2button"));
//Serial.println(side2Button);

//********************************************************************************************

//Check Buttons

      if (digitalRead(20) == LOW){//side 1 of stack ready to rip
        side1Button =1;
      }
      if (digitalRead(21) == LOW){//side 1 of stack ready to rip
        side2Button =1;
      }

//********************************************************************************************
//FIRST RUN BRINGS PLATTENS BACK TO BOTTOM AFTER RESET/POWERING UP FOR FIRST TIME

if (firstRunComplete==false) {
  //enable motors
    digitalWrite(2, LOW); 
    
  //check if plattens are somehwere along Z or at bottom sensors
        //Motor 1
            if (digitalRead(15)==HIGH){ //sensor at bottom not engaged
                MoveMotor1 = 2; //send motor 1 DOWN    
            }
            if (digitalRead(15)==LOW){ //sensor at bottom engaged
                MoveMotor1 = 0; 
                side1atbottom = true; 
            }
        //Motor 2
            if (digitalRead(17)==HIGH){ //sensor at bottom not engaged
                MoveMotor2 = 2; //send motor 1 DOWN    
            }
            if (digitalRead(17)==LOW){ //sensor at bottom engaged
                MoveMotor2 = 0;
                side2atbottom = true; 
            }
  //check if everything is at the home position
  if (digitalRead(15) ==LOW && digitalRead(17) == LOW){
    firstRunComplete = true;
    waitbuttonstart = false;
  }
}
//******************************************************************************************
//user now chooses which side of stack to start with
  if (firstRunComplete ==true && waitbuttonstart == false){
    if (side1Button == 1 && side2Button ==0){
      side2attop=true;
      waitbuttonstart = true;
      delay(1000);
    }
    if (side1Button == 0 && side2Button ==1){
      side1attop=true;
      waitbuttonstart = true;
      delay(1000);
    }
    if (side1Button == 1 && side2Button ==1){
      side2attop=true;
      waitbuttonstart = true;
      delay(1000);
    }
    
  }

//*********************************************************************************************          
//Sensor Logic 

if (firstRunComplete==true && waitbuttonstart ==true){

//move platen 1 up if throughbeam is not being interupted
  if (side1atbottom==true && side1Button == 1 && side2attop == true && digitalRead(18)==LOW){
    MoveMotor1 = 1; //up
    side1attop = false;
    indexup = 0;
  }
  
  if (side1atbottom==true && side1Button == 1 && side2attop == true && digitalRead(18)==HIGH){
   if (indexup < 5){
    delay(300); //delay to increase the level of the badges
    }
    digitalWrite(0, HIGH); //Turn motor 1 INPUT A OFF; //halt the motor
    delay(1000);
    GoGoRotato();
    indexup++;
    //Serial.println("stop");
    delay(1000);
  }
  
  if (digitalRead(14) == LOW){
    MoveMotor1 = 2; //down
    side1atbottom = false;
    side1attop = true;
    side1Button = 0;
  }
  
  if (digitalRead(15) == LOW && side1attop ==true){
    side1atbottom =true;
    MoveMotor1 = 0; //halt
  }
  //move platen 2 up if throughbeam is not being interupted
  if (side2atbottom==true && side2Button == 1 && side1attop == true && digitalRead(18)==LOW){
    MoveMotor2 = 1; //up
    side2attop = false;
    indexup = 0;
  }
  if (side2atbottom==true && side2Button == 1 && side1attop == true && digitalRead(18)==HIGH){
    if (indexup < 5){
    delay(300); //delay to increase the level of the badges
    }
    digitalWrite(3, HIGH); //Turn motor 2 INPUT A OFF; //halt
    delay(1000);
    GoGoRotato();
    //Serial.println("stop");
    indexup++;
    delay(500);
  }
//  // high Switch - Debounce using a 'millis' timer
//    if (digitalRead(16) == LOW) {
//      
//  // check if enough time has passed to consider it a switch press
//      if ((millis() - Debounce) > 100) {
//        MoveMotor2 = 2; //down
//        side2atbottom = false;
//        side2attop = true;
//        side2Button = 0;
//      }
//    }
  if (digitalRead(16) == LOW){
    MoveMotor2 = 2; //down
    side2atbottom = false;
    side2attop = true;
    side2Button = 0;
  }
  if (digitalRead(17) == LOW && side2attop ==true){
    side2atbottom =true;
    MoveMotor2 = 0; //halt
  }
    
  if (digitalRead(19)==LOW){ //reset button pressed
    MoveMotor1 = 0; //halt
    MoveMotor2 = 0; //halt
    firstRunComplete = false;
    waitbuttonstart = false;
    side1Button = 0;
    side2Button = 0;
  }
}
//******************************************************************************************
//moving the motors outside the if.
          //Motor 1
          if (MoveMotor1 == 2){ //down
            digitalWrite(0, HIGH); //Turn motor 1 INPUT A OFF
            digitalWrite(1, LOW); //Turn motor 1 INPUT B ON
          
          }
          if (MoveMotor1 == 0){ //halt
            digitalWrite(0, HIGH); //Turn motor 1 INPUT A OFF
            digitalWrite(1, HIGH); //Turn motor 1 INPUT B OFF
           
          }
          if (MoveMotor1 == 1){ //up
            digitalWrite(0, LOW); //Turn motor 1 INPUT A ON
            digitalWrite(1, HIGH); //Turn motor 1 INPUT B OFF
          }
          //Motor 2
          if (MoveMotor2 == 2){ //down
            digitalWrite(3, HIGH);  //Turn motor 2 INPUT A OFF
            digitalWrite(4, LOW);   //Turn motor 2 INPUT B ON
          }
          if (MoveMotor2 == 0){ //halt
            digitalWrite(3, HIGH); //Turn motor 2 INPUT A OFF
            digitalWrite(4, HIGH); //Turn motor 2 INPUT B OFF
            
          }
          if (MoveMotor2 == 1){ //up
            digitalWrite(3, LOW); //Turn motor 2 INPUT A ON
            digitalWrite(4, HIGH); //Turn motor 2 INPUT B OFF
          }
      }      
//*****************************************************************************************
void GoGoRotato(){
// need to have delays between relays and inputs and outputs of air - seems to affect the controller.
//rotate from belt position to badge position
    //(5) off (6) on
    digitalWrite(7, LOW);
    delay(500);
    digitalWrite(6, LOW);
    delay(900); 
    //Turn on Suckers
    digitalWrite(6, HIGH); 
    delay(1300); // added
    digitalWrite(7, LOW);
    delay(500);
//rotate form badge position to belt position
  digitalWrite(5, LOW);
  delay(1000); 
  digitalWrite(5, HIGH); 
  delay(1200); 
    //Turn off Suckers
      digitalWrite(7, HIGH);
      delay(1000); //must keep!

}










  
//  //Motor 1 moving up, hits sensor then moves down
//      //Sensor 1 Higher is triggered
//          if (digitalRead(14) == LOW){
//            digitalWrite(0, HIGH); //Turn motor 1 INPUT A OFF
//              //for the cycle counter
//              if (Direction1Down ==false){
//                leftrightcycles=leftrightcycles+1; //increment cycle counter
//                Serial.print("the amount of cycles is: ");
//                Serial.println(leftrightcycles);
//                }
//            Direction1Down=true; 
//          }
//        
//  //Motor 1 moving down, hits sensor then waits for button trigger to move up
//     //Sensor 1 Lower is triggered
//            if (digitalRead(15) == LOW){
//            digitalWrite(1, HIGH); //Turn motor 1 INPUT B OFF
//              if (digitalRead(20) == HIGH){ //Button to say "I'm Refilled and Ready"
//              Direction1Down=false; //sets the direction to move to up
//              }
//          }
//
//          
//  //Motor 2 moving up, hits sensor then moves down
//     //Sensor 2 Higher is triggered
//          if (digitalRead(16) == LOW){
//            digitalWrite(3, HIGH); //Turn motor 2 INPUT A OFF
//            Direction2Down=true;
//          }
//  //Motor 2 moving down, hits sensor then moves up
//     //Sensor 2 Higher is triggered
//          if (digitalRead(17) == LOW){
//            digitalWrite(4, HIGH); //Turn motor 2 INPUT B OFF
//            Direction2Down=false;
//          }
////moving the motors outside the if.
//          if (Direction2Down == true){
//            digitalWrite(4, LOW); //Turn motor 2 INPUT B ON
//          }
//          if (Direction2Down == false){
//            digitalWrite(3, LOW); //Turn motor 2 INPUT A ON
//          }
//        
//    
