#include <Arduino.h>
#include <string.h>
#include <WiFi.h>
#include <AsyncUDP.h>

class Target {
    public:
        Target(String ssid , String password);
        void connect();
        void sendCommand(String commmand);
        void setIp(String ip);
        bool connected;
        String myIp;
        void loop();
        void commandResponse(String response);
        void ButtonPressed();

        WiFiUDP udpSender;
        const int udpPort = 7007; 
        AsyncUDP udp;

    private:
        String response;
        String ssid;
        String password;
        String droneIp = "10.0.0.4";
};