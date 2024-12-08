#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <NewPing.h>
#include <SoftwareSerial.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 50 // Distance maximum en cm pour les mesures

SoftwareSerial BTSerial(12,11);

enum RobotState {
  START,
  GO,
  STOP,
  BACK,
};

unsigned int distance; 

RobotState currentState = START;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

//counter for the 5 times
int count = 0; 

// Shield Initialization
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Left motor on MOTOR1
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);

// Right motor on MOTOR2
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

unsigned long startMillis; 
unsigned long currentMillis;  

void setup() {
  // Initialize the Shield
  AFMS.begin(); 
  // Set the initial speed of the motors (values between 0 and 255)
  leftMotor->setSpeed(30);
  rightMotor->setSpeed(30);
  Serial.begin(9600);
  BTSerial.begin(9600);
  startMillis = millis();
}

void loop() {

  currentMillis = millis();
  if (currentMillis - startMillis >= 30000) {
    currentState = STOP;
  }

  switch (currentState) {
    case START:
      Serial.println("Robot in START mode");
      leftMotor->run(RELEASE);
      rightMotor->run(RELEASE);

      if(sensorMesure()){
        count++;
        Serial.print("Count: ");
        Serial.println(count);
        if(count == 5){
          currentState = STOP; 
        }else{
          sendBluetoothMessage("Direction: GO");
          currentState = GO; 
        }
      }
      break;

    case GO:
      Serial.println("Robot in GO mode");
      leftMotor->run(FORWARD);
      rightMotor->run(FORWARD);

      if(sensorMesure()){
        count++;
        Serial.print("Count: ");
        Serial.println(count);
        if(count == 5){
          currentState = STOP; 
        }else{
          moteurGauche->run(RELEASE);
          moteurDroit->run(RELEASE);
          delay(1000);
          sendBluetoothMessage("Direction: BACK");
          currentState = BACK; 
        }
      }
      break;

    case BACK:
      Serial.println("Robot in BACK mode");
      leftMotor->run(BACKWARD);
      rightMotor->run(BACKWARD);

      if(sensorMesure()){
        count ++;
        if(count == 5){
          currentState = STOP; 
        }else{
          moteurGauche->run(RELEASE);
          moteurDroit->run(RELEASE);
          delay(1000);
          sendBluetoothMessage("Direction: GO");
          currentState = GO;
        }
      }
      break;

    case STOP:
      Serial.println("Robot in STOP mode");
      leftMotor->run(RELEASE);
      rightMotor->run(RELEASE);
      break;

    default:
      Serial.println("Unknown state");
      break;
  }

  delay(1000);
}
bool sensorMesure(){
  distance = sonar.ping_cm();

  if (distance > 0 && distance < MAX_DISTANCE) {  
    Serial.println("OBSTACLE DETECTE!!");
    return true;
  } else {
    Serial.println("Aucun obsatcle");
  }
  return false; 
}

void sendBluetoothMessage(String message) {
    BTSerial.println(message);
    Serial.println("Sent: " + message);
}