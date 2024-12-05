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

// Initialisation du Shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Moteur gauche sur MOTOR1
Adafruit_DCMotor *moteurGauche = AFMS.getMotor(1);

// Moteur droit sur MOTOR2
Adafruit_DCMotor *moteurDroit = AFMS.getMotor(2);

unsigned long startMillis; 
unsigned long currentMillis;  

void setup() {
  // Initialiser le Shield
  AFMS.begin(); 
  // Définir la vitesse initiale des moteurs (valeurs entre 0 et 255)
  moteurGauche->setSpeed(30);
  moteurDroit->setSpeed(30);
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
      Serial.println("Robot en mode START");
      moteurGauche->run(RELEASE);
      moteurDroit->run(RELEASE);
      }
      
      break;

    case GO:
      Serial.println("Robot en mode GO");
      moteurGauche->run(FORWARD);
      moteurDroit->run(FORWARD);
      break;

    case BACK:
      Serial.println("Robot en mode BACK");
      moteurGauche->run(BACKWARD);
      moteurDroit->run(BACKWARD);
      break;

    case STOP:
      Serial.println("Robot en mode STOP");
      moteurGauche->run(RELEASE);
      moteurDroit->run(RELEASE);
      break;

    default:
      Serial.println("Etat inconnu");
      break;
      
    delay(1000);
}
