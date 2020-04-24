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
            //this->lastRead = this->readPotentiometer();
        }

        int readPotentiometer(){
            int heightVal = (analogRead(pNumber) * 60) / 4095;
            return heightVal;
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

        bool hasChanged()
        {
            return abs(lastRead-analogRead(pNumber)) > sensitivity;
        }

        void setWarning(String message)
        {

        }

        void setInfo(String message)
        {
            this->infoMessage = message;
        }

        void loop()
        {
            if (this->hasChanged())
            {
                int digiRead = digitalRead(this->pNumber);
                
                if (this->hasChanged() && this->infoMessage.length() > 0)
                {
                    Serial.println(this->infoMessage);
                }
                if ((digiRead == 0 || digiRead == 4095) && this->warningMessage.length() > 0);
                {
                    Serial.println(this->warningMessage);
                }
            }
        }
};