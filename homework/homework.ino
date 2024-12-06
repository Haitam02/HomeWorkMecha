#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <NewPing.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(12,11);

enum RobotState {
  START,
  GO,
  STOP,
  BACK,
};

RobotState currentState = START;

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
      break;

    case GO:
      Serial.println("Robot in GO mode");
      leftMotor->run(FORWARD);
      rightMotor->run(FORWARD);
      break;

    case BACK:
      Serial.println("Robot in BACK mode");
      leftMotor->run(BACKWARD);
      rightMotor->run(BACKWARD);
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

void sendBluetoothMessage(String message) {
    BTSerial.println(message);
    Serial.println("Sent: " + message);
}