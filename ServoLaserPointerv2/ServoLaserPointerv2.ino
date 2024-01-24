#include <Servo.h>

Servo horizontalServo;
Servo verticalServo;

const int touchPin = 3;

int minHorizontalAngle = 45;
int maxHorizontalAngle = 135;
int minVerticalAngle = 30;
int maxVerticalAngle = 60;

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

bool run = false;

void setup() {
  pinMode(touchPin, INPUT);

  // put your setup code here, to run once:
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
  int sensorValue = digitalRead(touchPin);
  if (sensorValue == 1){
    run = true;
  }

  if (run == false){
    return;
  }

  horizontalAngle = horizontalServo.read();
  Serial.println("Horizontal Angle: " + (String)horizontalAngle);
  if (abs(horizontalAngleToGoTo - horizontalAngle) <= abs(horizontalSpeed) + 5){
    //Reached Destination
    horizontalAngleToGoTo = random(minHorizontalAngle, maxHorizontalAngle + 1);
    Serial.println("Horizontal Angle To Go To: " + (String)horizontalAngleToGoTo);
    horizontalSpeed = random(minSpeed, maxSpeed + 1);
    Serial.println("Horizontal Speed" + (String)horizontalSpeed);
    if (horizontalAngleToGoTo < horizontalAngle){
      horizontalSpeed *= -1;
    }
  }
  else{
    Serial.println("Horizontal Go To - Horizontal Angle: " + (String)(abs(horizontalAngleToGoTo - horizontalAngle)));
    horizontalServo.write(horizontalAngle + horizontalSpeed);
  }

  verticalAngle = verticalServo.read();
  Serial.println("vertical Angle: " + (String)verticalAngle);
  if (abs(verticalAngleToGoTo - verticalAngle) <= abs(verticalSpeed) + 5){
    //Reached Destination
    verticalAngleToGoTo = random(minVerticalAngle, maxVerticalAngle + 1);
    Serial.println("vertical Angle To Go To: " + (String)verticalAngleToGoTo);
    verticalSpeed = random(minSpeed, maxSpeed + 1);
    Serial.println("vertical Speed" + (String)verticalSpeed);
    if (verticalAngleToGoTo < verticalAngle){
      verticalSpeed *= -1;
    }
  }
  else{
    Serial.println("vertical Go To - vertical Angle: " + (String)(abs(verticalAngleToGoTo - verticalAngle)));
    verticalServo.write(verticalAngle + verticalSpeed);
  }

}