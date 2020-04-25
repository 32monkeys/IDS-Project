#include <Arduino.h>
#include "WiFi.h"
#include "AsyncUDP.h"
#include <Target.h>
#include <Potentiometer.h>
#include <Controller.h>
#include <Timer.h>

int pinX = 34;
int pinY = 35;
int prevX;
int prevY;
int tolerance = 20;
Potentiometer potentiometer(36);
Controller controller(34,35,32);
Timer timer(50);


Target drone("NETGEAR61","ME262emp");

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
  if(timer.check()){
    String potRead = (String) potentiometer.readPotentiometer() + ","; 
    String contX = (String) controller.xReadController() + ",";
    String contY = (String) controller.yReadController() + ",";
    String butRead = (String) controller.butReadController();
    String result = (String) potRead + contX + contY + butRead;
    
    Serial.println(result);

    drone.sendCommand(result);
  }
}