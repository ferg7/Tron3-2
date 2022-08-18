#include <Arduino.h>

/*
Set up with 1 board 1st then worry about two doors

Can look at do an automated set up or put this in the report as future work?
*/


//Parameters
const int micPin=A0;

//Variables
int micVal=0;
int serialRate = 57600;
boolean doorOneOpen = false;


void setup() {

  //initialise acc and Gyro 

  //initialise serial
  Serial.begin(serialRate); 

  //establish web socket connection
}


//Accelerometer
int * readAcc (){
    static int acceleration[3];

    return acceleration
}

void * printAcc(acceleration){
    Serial.println(acceleration);
}



//Microphone
int readMic () {
    micVal = analogRead(micPin);
    return micVal;
}

void printMic(int micVal){
    Serial.println(micVal);
}


void sendSignal (String message, int door){
    //Code to send the signal to the right door
}


//main
void loop() {
  // Read data
    //read IMU data 
    // read microphone data


  //process for knocking 
  // test for knocking 
  //If knocking
    //Send update to user
  

  // track door position 
  // detect change?
  // If change 
    //loop untill position is reached 
    //update global door state?
    //send update to user
}