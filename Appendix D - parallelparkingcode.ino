const int trigPin = 32;  //pin 32 connected to the trigger pin of the HC-SR04
const int echoPin = 26;  //pin 26 connected to the echo pin of the HC-SR04
int angle = 0; //variable to store the angle measured by the MPU6050
int distance = 999; //variable to store the distance measured by the HC-SR04
long duration; //variable to store the duration of the HC-SR04 pulse
float distancecm; //variable to store the distance in cm
int leftMotor_speed, rightMotor_speed, servoAngle; //variables to store the motor speeds and servo angle
#include <math.h> //include math library for use with MPU6050
#include <MPU6050_tockn.h> //include MPU6050 library
#include <Wire.h> //include Wire library for I2C communication
MPU6050 mpu6050(Wire);  //create an instance of the MPU6050 class using the Wire library
#define I2C_SLAVE_ADDR 0x04  //define I2C slave address as 4 in hexadecimal
int x = 0;  //variable to store data for transmission

void setup()
{
  Serial.begin(9600); //start serial communication at 9600 baud
  Wire.begin();  //join I2C bus (address optional for the master) - on the Arduino NANO the default I2C pins are A4 (SDA), A5 (SCL)
  pinMode(trigPin, OUTPUT);  //sets the trigPin as an Output
  pinMode(echoPin, INPUT);  //sets the echoPin as an Input
  mpu6050.begin();  //initialize the MPU6050
  mpu6050.calcGyroOffsets(true);  //calculate gyro offsets
  Serial.print("\tangleZ : ");          //print label
  Serial.println(mpu6050.getAngleZ());  //print the angle measured by the MPU6050
}

void loop()
{
  //Forward 1 second
  leftMotor_speed = 150;
  rightMotor_speed = 150;
  servoAngle = 88;
  Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);  //transmit data to arduino
  delay(1000);
  //stop
  leftMotor_speed = 0;
  rightMotor_speed = 0;
  servoAngle = 90;
  Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);  //transmit data to arduino
  delay(1000);
    //Rotate 180 degrees
  leftMotor_speed = 250;
  rightMotor_speed = 100;
  servoAngle = 125;
  Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);  //transmit data to arduino
  while (angle = -180 ) {  //loop until angle is equal to -180
    angle = accelerometer();  //get angle from accelerometer
  }
  
   //stop
  leftMotor_speed = 0;
  rightMotor_speed = 0;
  servoAngle = 90;
  Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);  //transmit data to arduino
  delay(3000);

//reverse until 10cm away from wall
  leftMotor_speed = -100;
  rightMotor_speed = -100;
  servoAngle = 90;
  Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);
  do {
    distance = ultrasonic();
    delay(100);
  }
  while (distance >= 10);
  distance = 999;
 //stop
  leftMotor_speed = 0;
  rightMotor_speed = 0;
  servoAngle = 90;
  Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);
  delay(3000);
  
  leftMotor_speed = 100;
  rightMotor_speed = 250;
  servoAngle = 55;
  Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);
  while (angle <= -90) {
    angle = accelerometer();
  }
   //stop
  leftMotor_speed = 0;
  rightMotor_speed = 0;
  servoAngle = 90;
  Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);
  delay(5000);
 
    //stop
  leftMotor_speed = 0;
  rightMotor_speed = 0;
  servoAngle = 90;
  Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);
  delay(1000);
   //reverse until 10cm away from wall
  leftMotor_speed = -100;
  rightMotor_speed = -100;
  servoAngle = 90;
  Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);
  do {
    distance = ultrasonic();
    delay(100);
  }
  while (distance >= 10);
  distance = 999;
 //stop
  leftMotor_speed = 0;
  rightMotor_speed = 0;
  servoAngle = 90;
  Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);
  delay(50000);


}

void Transmit_to_arduino(int leftMotor_speed, int rightMotor_speed, int servoAngle)
{
  Wire.beginTransmission(I2C_SLAVE_ADDR); // transmit to device #4
  Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));    // first byte of leftMotor_speed, containing bits 16 to 9
  Wire.write((byte)(leftMotor_speed & 0x000000FF));           // second byte of leftMotor_speed, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));   // first byte of rightMotor_speed, containing bits 16 to 9
  Wire.write((byte)(rightMotor_speed & 0x000000FF));          // second byte of rightMotor_speed, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));         // first byte of servoAngle, containing bits 16 to 9
  Wire.write((byte)(servoAngle & 0x000000FF)); // second byte of servoAngle, containing the 8 LSB - bits 8 to 1
  Wire.endTransmission();   // stop transmitting
}

//function to get angle from accelerometer
float accelerometer()
{
  mpu6050.update();  //update the MPU6050 values
  Serial.print("\tangleZ : ");  //print label
  Serial.println(mpu6050.getAngleZ());  //print the angle measured by the MPU6050
  return mpu6050.getAngleZ();  //return the angle
}
//function to get distance from ultrasonic sensor
float ultrasonic()
{
  float distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return (duration * 0.034 / 2);
}
