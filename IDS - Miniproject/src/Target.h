#include <Arduino.h>
#include <string.h>
#include <WiFi.h>
#include <AsyncUDP.h>

class Target {
    private:
        String response;
        String ssid;
        String password;
        String droneIp = "10.0.0.4";
    public:
        bool connected;
        String myIp;
        WiFiUDP udpSender;
        const int udpPort = 7007; 
        AsyncUDP udp;
        String command;

        Target(String ssid , String password){
            this->ssid = ssid;
            this->password = password; 
        }

        void connect(){
            WiFi.mode(WIFI_STA);
            WiFi.begin(this->ssid.c_str(), this->password.c_str());
            if (WiFi.waitForConnectResult() != WL_CONNECTED) {
                Serial.println("WiFi Failed");
                while(1) {
                    delay(1000);
                }
            }
            if(udp.listen(udpPort)) {
                myIp = WiFi.localIP().toString();
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
                        commandResponse(s);
                    }
                );
            }
        }

        void sendCommand(String command) {
            udpSender.beginPacket("10.0.0.4", udpPort);
            udpSender.printf(command.c_str());
            udpSender.endPacket();    
        }

        void commandResponse(String response)   {
            Serial.print("got following response: ");
            Serial.println(response.c_str());
            Serial.print("message length: ");
            Serial.println(response.length());
        }
};