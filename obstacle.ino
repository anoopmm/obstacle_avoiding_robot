//ARDUINO OBSTACLE AVOIDING CAR//
// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library//-install //
//NewPing Library https://github.com/livetronic/Arduino-NewPing// 
//Servo Library https://github.com/arduino-libraries/Servo.git //
// To Install the libraries go to sketch >> Include Library >> ManageLibrary
//search and download library


#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A5 
#define ECHO_PIN A4 
#define MAX_DISTANCE 200 
#define MAX_SPEED 70 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
AF_DCMotor rightBack(1);                          //Create an object to control each motor
AF_DCMotor rightFront(4);
AF_DCMotor leftFront(3);
AF_DCMotor leftBack(2);

//AF_DCMotor motor1(1, MOTOR12_1KHZ); 
//AF_DCMotor motor2(2, MOTOR12_1KHZ);
//AF_DCMotor motor3(3, MOTOR34_1KHZ);
//AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;
int speedOffset=10;

void setup() {

  myservo.attach(9);  
  myservo.write(90); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
 if(distance<=25)
 {
  moveStop();
  delay(200);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
}

int lookRight()
{
    myservo.write(0); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(90); 
    return distance;
}

int lookLeft()
{
    myservo.write(180); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(90); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  rightBack.run(RELEASE); 
  rightFront.run(RELEASE);
  leftFront.run(RELEASE);
  leftBack.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    rightBack.run(FORWARD);      
    rightFront.run(FORWARD);
    leftFront.run(FORWARD); 
    leftBack.run(FORWARD);     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    rightBack.setSpeed(speedSet);
    rightFront.setSpeed(speedSet);
    leftFront.setSpeed(speedSet+speedOffset);
    leftBack.setSpeed(speedSet+speedOffset);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    rightBack.run(BACKWARD);      
    rightFront.run(BACKWARD);
    leftFront.run(BACKWARD);
    leftBack.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    rightBack.setSpeed(speedSet);
    rightFront.setSpeed(speedSet);
    leftFront.setSpeed(speedSet);
    leftBack.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  leftFront.run(FORWARD);
  leftBack.run(FORWARD);
  rightFront.run(BACKWARD);
  rightBack.run(BACKWARD);     
  delay(800);
  leftFront.run(FORWARD);      
  leftBack.run(FORWARD);
  rightFront.run(FORWARD);
  rightBack.run(FORWARD);      
} 
 
void turnLeft() {
  leftFront.run(BACKWARD);     
  leftBack.run(BACKWARD);  
  rightFront.run(FORWARD);
  rightBack.run(FORWARD);   
  delay(825);
  leftFront.run(FORWARD);     
  leftBack.run(FORWARD);
  rightFront.run(FORWARD);
  rightBack.run(FORWARD);
}  
