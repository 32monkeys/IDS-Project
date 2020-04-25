#include <Arduino.h>

class Timer {
    public:
        long interval;
        unsigned long currentMillis = millis();
        unsigned long previousMillis = 0;

        Timer(long interval){
            this->interval = interval;
        };
    
        bool check(){
            currentMillis = millis();
            if(currentMillis - previousMillis > interval){
                previousMillis = currentMillis;
                return true;
            } else {
                return false;
            }
    }
};
