#include <Arduino.h>
#include <Target.h>
#include <string.h>
#include <WiFi.h>
#include <AsyncUDP.h>

String ssid;
String password;

String response = "";

Target::Target(String ssid, String password){
    this->ssid = ssid;
    this->password = password; 
}

void Target::connect(){
WiFi.mode(WIFI_STA);
WiFi.begin(this->ssid.c_str(), this->password.c_str());
if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    while(1) {
        delay(1000);
    }
}

if(udp.listen(udpPort)) {
    this->myIp = WiFi.localIP().toString();
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());
    
    Serial.println("onPacket");
    
    udp.onPacket(
        [this](AsyncUDPPacket packet) -> void
        {
            // make a string from the data
            String s((char*)packet.data());
            s = s.substring(0, packet.length()); 
            s.trim();
            // send string to method
            this->commandResponse(s);
        }
    );
    this->sendCommand("command");
}

}

void Target::sendCommand(String command) {
    udpSender.beginPacket(this->droneIp.c_str(), udpPort);
    udpSender.printf(command.c_str());
    udpSender.endPacket();    
}

void Target::setIp(String ip) {
    this->droneIp = ip;
}
        
void Target::commandResponse(String response) {
    Serial.print("got following response: ");
    Serial.println(response.c_str());
    Serial.print("message length: ");
    Serial.println(response.length());
}