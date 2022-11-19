#include <Servo.h>
Servo s1;
Servo s2;
Servo s3;

/*
 * The length between the rotation top piece * bottom servo center is 50 mm
 * The length between the center of the ball and the middle of the bottom servo is 100 mm
 */

double l1 = 50;
double l2 = 100;
double h = 80; //80 is the highest the leg can go safely; 0 would be inside the servo; 150 is max theoretical extension
int deltaTime = 5;
double fwdTanAngle;
double crabTanAngle;
double angle1;
double angle2;
double angle3;

void setup() {
  Serial.begin(115200);
  s1.attach(3,360,2300);
  s2.attach(5,360,2300);
  s3.attach(6,360,2300);
}

double squareValue(double val) {
  return(val * val);
}

void findAngles(double height, double pos) {
  double l3 = sqrt(squareValue(height) + squareValue(pos));
  angle3 = (180 / PI) * acos((squareValue(l1) + squareValue(l2) - squareValue(l3)) / (2 * l1 * l2));
  angle2 = (180 / PI) * acos((squareValue(l1) + squareValue(l3) - squareValue(l2)) / (2 * l1 * l3));
  angle1 = (180 / PI) * acos((squareValue(l3) + squareValue(l2) - squareValue(l1)) / (2 * l3 * l2));
  fwdTanAngle = (180 / PI) * (atan(pos / height));
  Serial.print("3: ");
  Serial.println(angle3);  
  Serial.print("2: ");
  Serial.println(angle2);
  Serial.print("1: ");
  Serial.println(angle1);
  Serial.print("angle2 - angle: ");
  Serial.println(angle2 - fwdTanAngle);
  /*Serial.println(angle1);
  Serial.println(angle2);
  Serial.println(angle3);*/
}

void loop() {
  for(int i = -60; i <= 60; i ++) {
    double extAngle = (180 / PI) * atan(i / h);
    double j = sqrt((i * i) + (h * h));
    findAngles(j,60);
    s1.write(90 + angle1);
    s2.write(90 - (angle2 - angle));
    s3.write(angle3);
    delay(deltaTime);
  }
  delay(250);
}


  /*h = 95;
  for(int i = 100; i >= 0; i --) {
    findAngles(h,i);
    s1.write(90);
    s2.write(90 - (angle2 - angle));
    s3.write(angle3);
    delay(deltaTime);
  }
  h = 75;
  for(int i = 0; i <= 100; i ++) {
    findAngles(h,i);
    s1.write(90);
    s2.write(90 - (angle2 - angle));
    s3.write(angle3);
    delay(deltaTime);
  }*/
