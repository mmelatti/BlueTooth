#include <SoftwareSerial.h>//import the serial library
#include <Servo.h>

//notice locked = 180 unlocked = 0;

Servo myservo;

int servopos = 0;
int bluetoothTx = 10;
int bluetoothRx = 11;
int posTop = 0;
int lightSensorPin = 0;
int lightSensor;
int timerCounter = 0;
int prevoiusServopos = 0;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
myservo.attach(9);
//Setup usb serial connection to computer
Serial.begin(9600);

//Setup Bluetooth serial connection to android
bluetooth.begin(9600);
}

void loop()
{
  
if(bluetooth.available()> 0 )
{
  servopos = bluetooth.read();
  
} else { 
  if(lightSensor < 500){ //If it is dark for a significant amount of time the user is assumed asleep, the door is automatically locked
    myservo.write(180); 
  } else {                //otherwise, the door will follow whatever command the user last entered, if it was locked it will stay locked
    myservo.write(servopos);  
  }
}

lightSensor = analogRead(lightSensorPin);
Serial.println(lightSensor);

}

