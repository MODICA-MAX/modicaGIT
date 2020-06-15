//This Program was installed at the Latern Press Factory on 5/27/2020
//Pogram by Max Cerami

//declare variables

      boolean firstRunComplete = false; //variable for doing 1 loop at begining of each program. resets plattens at bottom of infeed stack
      boolean waitbuttonstart = false;  //variable to wait for user to choose which stack to start with.
      boolean side1atbottom = false;    //variable for stating whether platten 1 is at bottom
      boolean side2atbottom = false;    //variable for stating whether platten 2 is at bottom
      boolean side1attop = false;       //variable for stating whether platten 1 is at top
      boolean side2attop = false;       //variable for stating whether platten 2 is at top
      boolean returnarbor = false;      //variable to move arbor of rotato to conveyor side upon startup
      boolean pausesystem = false;      //var for pausing system
      
      int MoveMotor1 = 0; //using to halt motor (0), move up (1), move down (2)
      int MoveMotor2 = 0;
      int indexup = 0; //var used to give the badgebot a number of tries at indexing the level of the badges up before it does not ratchet them up any more incase it misses on first try
      
      int side1Button =0; //variable to store that side1 button has been pressed - side 1 stack ready to feed (1) or not ready (0)
      int side2Button =0; //variable to store that side1 button has been pressed - side 2 stack ready to feed (1) or not ready (0)

void setup() {
 
  // declaring pins for Motor Control
      pinMode(0, OUTPUT); //motor 1 INPUT A
      pinMode(1, OUTPUT); //motor 1 INPUT B
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
      pinMode(19, INPUT);  //Pause...Retract Platforms
      pinMode(20, INPUT);  //Side 1 Ready
      pinMode(21, INPUT);  //Side 2 Ready

//pins for inputs and outputs to Magnet1.0

      pinMode(22, INPUT);  //input Magnet 1.0 machine ready signal. (Y7) in PLC code for Magnet 1.0
      pinMode(2, OUTPUT);  //Mini-Mag Ready signal (X1) in PLC code for Magnet 1.0

//disable all outputs upon startup
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
////debugging
//Serial.println(F("motor 1"));
//Serial.println(MoveMotor1);
//Serial.println(F("motor 2"));
//Serial.println(MoveMotor2);
////
//Serial.println(F("firstRunComplete"));
//Serial.println(firstRunComplete);
//Serial.println(F("waitbuttonstart"));
//Serial.println(waitbuttonstart);
////
//Serial.println(F("side1atbottom"));
//Serial.println(side1atbottom);
//Serial.println(F("side2atbottom"));
//Serial.println(side2atbottom);
//Serial.println(F("side1attop"));
//Serial.println(side1attop);
//Serial.println(F("side2attop"));
//Serial.println(side2attop);
////
//Serial.println(F("throughbeam"));
//Serial.println(digitalRead(18));
////
//Serial.println(F("side1button"));
//Serial.println(side1Button);
//Serial.println(F("side2button"));
//Serial.println(side2Button);
//
//Serial.println("indexup  ");
//Serial.print(indexup);
//********************************************************************************************

//Check Buttons

      if (digitalRead(20) == LOW){//side 1 of stack ready to rip
        side1Button =1;
      }
      if (digitalRead(21) == LOW){//side 1 of stack ready to rip
        side2Button =1;
      }
//********************************************************************************************
if (pausesystem==true) {//initiated when reset button is pressed once during feeding of stack 1 or 2.
  //tell the magnet 1.0 that we are not ready
      digitalWrite(2, HIGH); //(X1) is broken
      delay(2000); //prevents reset button being held too long and retracting without pausing.
  
  
  if (digitalRead(19)==LOW){ //reset button pressed again = retract platforms
      pausesystem=false;
      firstRunComplete = false; //this action kicks user back to inital state of machine
      waitbuttonstart = false;
      pausesystem = true;
      side1Button = 0;
      side2Button = 0;
      returnarbor=false;
      pausesystem=false;
  }
  //resume
  if (digitalRead(20) == LOW or digitalRead(21) == LOW){//side 1 or 2 resume
    pausesystem=false;
    
  }
  
}
//******************************************************************************************
//user chooses which side of stack to start with
  if (firstRunComplete ==true && waitbuttonstart == false && pausesystem==false){
    if (side1Button == 1 && side2Button ==0){//side 1 chosen to start
      side2attop=true;
      waitbuttonstart = true;
      delay(1000);
      returnarbor=false;
    }
    if (side1Button == 0 && side2Button ==1){//side 2 chosen to start
      side1attop=true;
      waitbuttonstart = true;
      delay(1000);
      returnarbor=false;
    }
    if (side1Button == 1 && side2Button ==1){//for some reason both are true
      side2attop=true;
      waitbuttonstart = true;
      delay(1000);
      returnarbor=false;
    }
    
  }
//********************************************************************************************
//FIRST RUN BRINGS PLATTENS BACK TO BOTTOM AFTER RESET/POWERING UP FOR FIRST TIME
//this is placed after pause and waitbutton start code for a reason.

if (firstRunComplete==false && pausesystem==false) {

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

//*********************************************************************************************          
//RUN MODE
if (firstRunComplete==true && waitbuttonstart ==true && pausesystem==false){


//SIDE 1 LOGIC

      //move platen 1 up if throughbeam is not being interupted
          if (side1atbottom==true && side1Button == 1 && side2attop == true && digitalRead(18)==LOW && side2atbottom ==true){ //DR(18) added to make sure side 2 at bottom before starting side 1. // since rotato uses delays, the platten of the side 2 would run into the hardstop if rotato was running.
            MoveMotor1 = 1; //up
            side1attop = false;
            indexup = 0; //reset the indexer
          }
        
      //stopping and engaging the pick and place routine
            if (side1atbottom==true && side1Button == 1 && side2attop == true && digitalRead(18)==HIGH && side2atbottom ==true){
              
                digitalWrite(2, LOW);  //tell Magnet 1.0 (x1) we are ready     
                
                if (digitalRead(22)==HIGH){  //input Mini-Mag 1.0 not ready. (y7)
                  MoveMotor1=0; //Halt
                }
                else{ //Magnet conveyor running
                    MoveMotor1 = 1; //up
                    if (indexup < 10){
                          delay(150); //delay to increase the level of the badges (this number is fiddly careful)
                          }
                    digitalWrite(0, HIGH); //Turn motor 1 INPUT A OFF; //halt the motor
                    delay(1000); //preventing relay bounce don't remove
                    GoGoRotato(); //call the rotato prog.
                    indexup++;
                    delay(500); //preventing relay bounce don't remove
                 }
             }
      //side 1 reaches the top sensor
                if (digitalRead(14) == LOW){ 
                  MoveMotor1 = 2; //down
                  side1atbottom = false;
                  side1attop = true;
                  side1Button = 0;
                  returnarbor=false;
                }
      //side 1 reaches the bottom sensor
                if (digitalRead(15) == LOW && side1attop ==true){
                  side1atbottom =true;
                  MoveMotor1 = 0; //halt
                }


//SIDE 2 LOGIC

      //move platen 2 up if throughbeam is not being interupted
                if (side2atbottom==true && side2Button == 1 && side1attop == true && digitalRead(18)==LOW && side1atbottom ==true){
                  MoveMotor2 = 1; //up
                  side2attop = false;
                  indexup = 0;
                }
        
      //stopping and engaging the pick and place routine
                if (side2atbottom==true && side2Button == 1 && side1attop == true && digitalRead(18)==HIGH && side1atbottom ==true){
                    
                    digitalWrite(2, LOW);  //tell Magnet 1.0 (x1) we are ready     
                    
                    if (digitalRead(22)==HIGH){  //input Mini-Mag 1.0 not ready. (y7)
                      MoveMotor2=0; //Halt
                    }
                    else{ //Magnet conveyor running
                        MoveMotor2 = 1; //up
                        if (indexup < 10){
                        delay(150); //delay to increase the level of the badges
                        }
                        digitalWrite(3, HIGH); //Turn motor 2 INPUT A OFF; HALT, this needed since movemotor command wouldn't be acted upon until after rotato program run.
                        delay(1000);
                        GoGoRotato();
                        indexup++;
                        delay(500);
                    }
                }

       //side 2 at top sensor
                if (digitalRead(16) == LOW){ 
                  MoveMotor2 = 2; //down
                  side2atbottom = false;
                  side2attop = true;
                  side2Button = 0;
                  returnarbor=false;
                  
                }
       //side 2 at bottom sensor
                if (digitalRead(17) == LOW && side2attop ==true){ 
                  side2atbottom =true;
                  MoveMotor2 = 0; //halt
                }
               
//other logic for starting/stopping
       
       //reset button pressed
                if (digitalRead(19)==LOW){ 
                  MoveMotor1 = 0; //halt
                  MoveMotor2 = 0; //halt
                  pausesystem=true;
                }
      //no bottons pressed i.e. stacks empty
        if (side1Button == 0 && side2Button ==0){
            digitalWrite(2, HIGH); //tell the magnet 1.0 that we are not ready
        }
      }
//******************************************************************************************
//Some Reset Logic
          //Return Arbor resets the Rotato to its initalized position. this prevents the suction cups from getting caught on the H gate.
          if (returnarbor == false){
            //return arbor to conveyor position
            digitalWrite(5, LOW);
            delay(1500); 
            //turn off rotato
            digitalWrite(5, HIGH); 
            delay(500); 
            returnarbor=true;
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
void GoGoRotato(){ //rotato programming.
// need to have delays between relays and inputs and outputs of air - seems to affect the controller.
//rotate from belt position to badge position
    //Turn on Suckers
        digitalWrite(7, LOW);
        delay(500);
    //go git that badge!
        digitalWrite(6, LOW);
        delay(1500); 
    //turn off rotation
        digitalWrite(6, HIGH); 
        delay(500);

//rotate form badge position to belt position (RUN AWAY!!!!!!)
      digitalWrite(5, LOW);
      delay(1500); 
      //turn off rotation
        digitalWrite(5, HIGH); 
      delay(500); 
      //Turn off Suckers
      digitalWrite(7, HIGH);
      delay(1000); //must keep!

}
