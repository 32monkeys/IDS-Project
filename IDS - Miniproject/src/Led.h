#include <Arduino.h>

class Led{
    public:
        
        int pinNumber;
        bool state;
        const int freq = 5000;
        const int ledChannel = 0;
        const int resolution = 8;

        Led(int pinNumber) {
            this->pinNumber = pinNumber;

            pinMode(this->pinNumber, OUTPUT);

            ledcSetup(this->ledChannel, this->freq, this->resolution);
            ledcAttachPin(this->pinNumber, this->ledChannel);
            
        }

        void setBrightness(int wait){
            // increase the LED brightness
            for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
                // changing the LED brightness with PWM
                ledcWrite(this->ledChannel, dutyCycle);
                delay(wait); // Hello world
            }

            // decrease the LED brightness
            for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
                // changing the LED brightness with PWM
                ledcWrite(this->ledChannel, dutyCycle);
                delay(wait);
            }
        
        }

        void on(){
            digitalWrite(this->pinNumber, HIGH);
            this->state=true;
        }

        void off(){
            digitalWrite(this->pinNumber, LOW);
            this->state=false;
        }
        
        String status(){
            String s;

            s += "LED on: ";
            s += this->pinNumber;
            s += " is ";
            if (!this->state){
                s += "off.";
            } 
            else if (this->state){
                s += "on.";
            } 
            else {
                s += "fucked.";
            }
            return s;

        }
};