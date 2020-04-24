#include <Arduino.h>
#include "WiFi.h"
#include "AsyncUDP.h"
#include <Arduino.h>
#include <Target.h>
#include <Potentiometer.h>
#include <Controller.h>

int pinX = 34;
int pinY = 35;
int prevX;
int prevY;
int tolerance = 20;
Potentiometer potentiometer(36);
Controller controller(34,35,32);
unsigned long currentMillis = millis();
unsigned long previousMillis = 0;
int interval = 200;

Target drone("wifi","password");

void setup() {
  potentiometer.setSensitivity(50);
  Serial.begin(9600);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(32, INPUT_PULLUP);
  prevX = analogRead(pinX);
  prevY = analogRead(pinY);  

  drone.connect();
}

void loop() {
  currentMillis = millis();
  if(currentMillis - previousMillis > interval){
    String potRead = (String) potentiometer.readPotentiometer() + ","; 
    String contX = (String) controller.xReadController() + ",";
    String contY = (String) controller.yReadController() + ",";
    String butRead = (String) controller.butReadController();
    String result = (String) potRead + contX + contY + butRead;
    
    Serial.println(result);

    drone.sendCommand(result);
    previousMillis = currentMillis;
  }
}