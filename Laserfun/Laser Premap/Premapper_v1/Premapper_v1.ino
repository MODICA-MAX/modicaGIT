
// From Robin2
// Example 5 - Receive with start- and end-markers combined with parsing

//====================================================================
// Parse code for GRBL CNC
// 13/11/2018
// Ver 0.2
//====================================================================

const byte numChars =71;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

//Feed and Speed variables
char FSMsgGRBL[12];
int FS_FeedMsg = 0;
int FS_SpeedMsg = 0;

//Overide variables
bool OvMsg = false; //Ov message being transmitted
int CmdCoolant = 0;
int CmdSpindleCW = 0;

//Laser Stuff
int LaserPin = A0;         // select the input pin for the Laser analog out
double LaserValue = 0;     // variable to store the value coming from the Laser
double LaserZeroValue=0;   //Var for setpoint of laser
double Z_Pos;              //Var for Z offset of Laser Value

// Variables to hold Message blocks

char Machine_State [numChars] = {0};
String STR_Machine_State;
char X_Pos [numChars] = {0}; //x position coordinate
char Y_Pos [numChars] = {0}; //y position coordinate
char GRBL_msg3 [numChars] = {0};
char GRBL_msg4 [numChars] = {0};
char GRBL_msg5 [numChars] = {0};
char GRBL_msg6 [numChars] = {0};


boolean newData = false;

//============

void setup() {
    Serial.begin(115200);
    //Serial.println("This demo expects 3 pieces of data - text, an integer and a floating point value");
    //Serial.println("Enter data in this style <HelloWorld, 12, 24.7>  ");
    Serial.println("Format of data read from GRBL");
    Serial.println("<Idle|MPos:0.000,0.000,0.000|Bf:15,128|FS:0,1000|Ov:100,100,100|A:SF>");
    Serial.println();
}

//============

void loop() {
    if (LaserZeroValue<1){
      LaserZeroValue=analogRead(LaserPin);
    }
    
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        //Read the Value on the Laser
         LaserValue = analogRead(LaserPin);
         
         //Serial.println(LaserValue);
          //Scale Value to get actual height in mm
        parseData();
        if (Machine_State[0] != 'I'){ // this makes it so data is only recorded when the machine is moving.
          showParsedData();
          XYlaser_data();
          
        }
        newData = false;
    }
}

//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = 'B';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

  //Parse into Blocks based on "|" Delimiter
 
        // machine state
            strtokIndx = strtok(tempChars,"|"); // Find first part of string (Machine State Idle, Run, Alarm)
            strcpy(Machine_State, strtokIndx);      // write characters from string to machine state variable
           
        // machine position   
            strtokIndx = strtok(NULL,":"); // look for next data block in string 
            strtokIndx = strtok(NULL,",");
            strcpy(X_Pos, strtokIndx); // write characters from string to machine position variable
            strtokIndx = strtok(NULL,",");
            strcpy(Y_Pos, strtokIndx); // write characters from string to machine position variable
        // BF god knows - alarms ?
           // strtokIndx = strtok(NULL,"|"); // look for next data block in string     
          //  strcpy(GRBL_msg3, strtokIndx); // write characters from string to BF variable 
           
        // feed and spindle speed
           // strtokIndx = strtok(NULL,"|"); // look for next data block in string     
           // strcpy(GRBL_msg4, strtokIndx); // write characters from string to Feed&Speed variable
             
        //Ov Overides 1% to 200%
           // strtokIndx = strtok(NULL,"|"); // look for next data block in string 
            //strcpy(GRBL_msg5, strtokIndx); // write characters from string to Overide variable
             
        //machine command status
            //strtokIndx = strtok(NULL,"|"); // look for next data block in string 
            //strcpy(GRBL_msg6, strtokIndx); // write characters from string to machine command status variable
           
        //anything else
   
}

 
//============

void showParsedData() {
 
  //Parse into Blocks based on "|" Delimiter
    //Serial.println("Message ");
    //Serial.println(Machine_State);
    //Serial.print(X_Pos);   
    //Serial.print(Y_Pos);
    //Serial.print(LaserValue); 
    //Serial.println(GRBL_msg3);
    //Serial.println(GRBL_msg4);
    //Serial.println(GRBL_msg5);
    //Serial.println(GRBL_msg6);
   // Serial.println(" ========== ");
   // Serial.println(FSMsgGRBL);
    //Serial.println(FS_FeedMsg);
    //Serial.println(FS_SpeedMsg);

}
//============

void XYlaser_data() {

Z_Pos = (LaserValue-LaserZeroValue)/5;

 Serial.print(X_Pos);
 Serial.print(" ");   
 Serial.print(Y_Pos);
 Serial.print(" ");
 Serial.print(Z_Pos);
 Serial.println();

}
