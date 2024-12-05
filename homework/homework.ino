#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <NewPing.h>


enum RobotState {
  START,
  GO,
  STOP,
  BACK,
};


RobotState currentState = START;

unsigned long startMillis;
unsigned long currentMillis; 

void setup() {
  Serial.begin(9600);
  startMillis = millis();
}

void loop() {

  currentMillis = millis();
  if (currentMillis - startMillis >= 30000) {
    currentState = STOP;
  }

  switch (currentState) {
    case START:
      
      break;

    case GO:
      
      break;

    case BACK:
      
      break;

    case STOP:
      
      break;

    default:
      Serial.println("Unknown State");
      break;
  }
  
}

