#include <Arduino.h>

class Potentiometer{
    public:
        int pNumber;
        int lastRead;
        int sensitivity;
        String z;
        String infoMessage = "";
        String warningMessage = "";

        Potentiometer(int pNumber)
        {
            this->pNumber = pNumber;
            pinMode(pNumber, INPUT);
        }

        int readPotentiometer(){
            int heightVal = (analogRead(pNumber) * 60) / 4095;
            return heightVal + 10;
        }

        String altitude(){
            this->lastRead = this->readPotentiometer();
            if (lastRead < readPotentiometer()) z = "UP";
            else if(lastRead > readPotentiometer()) z = "DOWN";
            else z = "STILL";
            return z;
        }

        void setSensitivity(int sensitivity)
        {
            this->sensitivity = sensitivity;
        }
};