/*
SparkFun Inventor’s Kit
Circuit 3C-Motion Alarm

Control the color of an RGB LED using an ultrasonic distance sensor. When an object is close to the sensor, buzz the buzzer and wiggle the servo motor.

This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
This code is completely free for any use.

View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

#include <Servo.h>                //include the servo library

const int trigPin = 11;           //connects to the trigger pin on the distance sensor       
const int echoPin = 12;           //connects to the echo pin on the distance sensor       

const int redPin = 3;             
const int greenPin = 5;           
const int bluePin = 6;            

const int buzzerPin = 10;         

float distance = 0;               

Servo myservo;                    
void setup()
{
  Serial.begin (9600);        

  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);    

 
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);   //set the buzzer pin to output

  myservo.attach(9);            //use pin 9 to control the servo

}

void loop() {
  distance = getDistance();   //variable to store the distance measured by the sensor

  Serial.print(distance);     //print the distance that was measured
  Serial.println(" in");      //print units after the distance

  if(distance <= 8){                         

    //make the RGB LED red
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);

    //this code wiggles the servo and beeps the buzzer
    tone(buzzerPin, 272);         
    myservo.write(45);            
    delay(100);                   

    noTone(buzzerPin);            
    myservo.write(135);          
    delay(100);                   


  } else if(9 < distance && distance < 20){  //if the object is a medium distance

    //make the RGB LED yellow
    analogWrite(redPin,255);
    analogWrite(greenPin, 100);
    analogWrite(bluePin, 0);

  } else{                                     //if the object is far away

    //make the RGB LED green
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);    
  }

  delay(50);      //delay 50ms between each reading
}

//------------------FUNCTIONS-------------------------------

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      
                                          

  calculatedDistance = echoTime / 148.0;  

  return calculatedDistance;              
}
