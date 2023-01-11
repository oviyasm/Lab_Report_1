
// Include encoder library
#include <Encoder.h>

//Enable pins with interrupt capability
Encoder myEnc(2, 11); 

//Set variables to track old position and distance travelled
long oldPosition = -999; 
float distance; 

//Set constants for pi, diameter of wheel (D) and number of encoders counts of revolution (N)
const float pi = 3.14;
const float D = 5.9;
const float N = 25;

void setup()
{
  //Set up serial communication, baud rate 9600
 Serial.begin(9600);
}

void loop()
{
 //Read the current position of the encoder 
 long newPosition = myEnc.read(); 

 // Check if encoder has moved
 if (newPosition != oldPosition)
 {
 //Update the old position
 oldPosition = newPosition; 

 // Calculate distance travelled using new encoder position
distance += (newposition * ((D*pi)/N));
 

 // output distance to the serial monitor
 Serial.print("Distance(m): ");
 Serial.println(distance);
 }
}
