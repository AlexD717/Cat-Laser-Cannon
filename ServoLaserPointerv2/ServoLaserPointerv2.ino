#include <Servo.h>

/*
Horizontal Servo - Pin 5
Vertical Servo - Pin 6
Motion Sensor (PIR) - Pin 3
*/

Servo horizontalServo;
Servo verticalServo;

int minHorizontalAngle = 0;
int maxHorizontalAngle = 90;
int minVerticalAngle = 10;
int maxVerticalAngle = 45;

float timeToGetToPosition = 0;
float minTime = 500;
float maxTime = 1000;

float horizontalAngle = minHorizontalAngle;
float verticalAngle = minVerticalAngle;
float horizontalAngleToGoTo;
float verticalAngleToGoTo;

float horizontalSpeed = 1;
float verticalSpeed = 1;
float minSpeed = 3;
float maxSpeed = 8;

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 10;        
float motionLastDetectedTime = 0;
float timeWithNoMotionToSwitch = 5000;

const int pirPin = 3;    //the digital pin connected to the PIR sensor's output

bool run = false;

void setup() {
  horizontalServo.attach(5);
  verticalServo.attach(6);

  horizontalServo.write(minHorizontalAngle);
  verticalServo.write(minVerticalAngle);
  delay(1000);
  horizontalServo.write(minHorizontalAngle);
  verticalServo.write(maxVerticalAngle);
  delay(1000);
  horizontalServo.write(maxHorizontalAngle);
  verticalServo.write(maxVerticalAngle);
  delay(1000);
  horizontalServo.write(maxHorizontalAngle);
  verticalServo.write(minVerticalAngle);
  delay(1000);
  horizontalServo.write(minHorizontalAngle);
  verticalServo.write(minVerticalAngle);
  delay(1000);

  Serial.begin(9600);

  //Motion Sensor Stuff
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
    }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);

  horizontalAngleToGoTo = random(minHorizontalAngle, maxHorizontalAngle + 1);
  Serial.println("Horizontal Angle To Go To: " + (String)horizontalAngleToGoTo);
  horizontalSpeed = random(minSpeed, maxSpeed + 1);
  Serial.println("Horizontal Speed" + (String)horizontalSpeed);
  if (horizontalAngleToGoTo < horizontalAngle){
    horizontalSpeed *= -1;
  }

  verticalAngleToGoTo = random(minVerticalAngle, maxVerticalAngle + 1);
  Serial.println("vertical Angle To Go To: " + (String)verticalAngleToGoTo);
  verticalSpeed = random(minSpeed, maxSpeed + 1);
  Serial.println("vertical Speed" + (String)verticalSpeed);
  if (verticalAngleToGoTo < verticalAngle){
    verticalSpeed *= -1;
  }
}

void loop() {

  if (digitalRead(pirPin) == HIGH){
    Serial.println("Motion Detected");
    motionLastDetectedTime = millis();
    run = true;
  }
  else{
    Serial.println("No Motion");
    if (millis() - motionLastDetectedTime >= timeWithNoMotionToSwitch){
      run = false;
    }
  }

  if (run == false){
    return;
  }

  horizontalAngle = horizontalServo.read();
  //Serial.println("Horizontal Angle: " + (String)horizontalAngle);
  if (abs(horizontalAngleToGoTo - horizontalAngle) <= abs(horizontalSpeed) + 5){
    //Reached Destination
    horizontalAngleToGoTo = random(minHorizontalAngle, maxHorizontalAngle + 1);
    //Serial.println("Horizontal Angle To Go To: " + (String)horizontalAngleToGoTo);
    horizontalSpeed = random(minSpeed, maxSpeed + 1);
    //Serial.println("Horizontal Speed" + (String)horizontalSpeed);
    if (horizontalAngleToGoTo < horizontalAngle){
      horizontalSpeed *= -1;
    }
  }
  else{
    //Serial.println("Horizontal Go To - Horizontal Angle: " + (String)(abs(horizontalAngleToGoTo - horizontalAngle)));
    horizontalServo.write(horizontalAngle + horizontalSpeed);
  }

  verticalAngle = verticalServo.read();
  //Serial.println("vertical Angle: " + (String)verticalAngle);
  if (abs(verticalAngleToGoTo - verticalAngle) <= abs(verticalSpeed) + 5){
    //Reached Destination
    verticalAngleToGoTo = random(minVerticalAngle, maxVerticalAngle + 1);
    //Serial.println("vertical Angle To Go To: " + (String)verticalAngleToGoTo);
    verticalSpeed = random(minSpeed, maxSpeed + 1);
    //Serial.println("vertical Speed" + (String)verticalSpeed);
    if (verticalAngleToGoTo < verticalAngle){
      verticalSpeed *= -1;
    }
  }
  else{
    //Serial.println("vertical Go To - vertical Angle: " + (String)(abs(verticalAngleToGoTo - verticalAngle)));
    verticalServo.write(verticalAngle + verticalSpeed);
  }

}