#include <Arduino.h>

class Controller{
    public:
        int xNumber;
        int yNumber;
        int butNumber;
        String xRead;
        String yRead;
        String butRead;
        String xDRead;
        String yDRead;
        String butDRead;

        Controller(int xNumber, int yNumber, int butNumber){
            this->xNumber = xNumber;
            this->yNumber = yNumber;
            this->butNumber = butNumber;
            pinMode(xNumber, INPUT);
            pinMode(yNumber, INPUT);
            pinMode(butNumber, INPUT_PULLUP);
            this->xRead = this->xReadController();
            this->yRead = this->yReadController();
            this->butRead = this->butReadController();
        }
        String xReadController(){
            if (analogRead(xNumber) < 300) xDRead = "LEFT";
            else if(analogRead(xNumber) > 3800) xDRead = "RIGHT";
            else xDRead = "STILL";
            return xDRead;
        }
        String yReadController(){
            if(analogRead(yNumber) < 300) yDRead = "FORWARD";
            else if(analogRead(yNumber) > 3800) yDRead = "BACKWARD";
            else yDRead = "STILL";
            return yDRead;
        }
        String butReadController(){
            if(analogRead(butNumber) < 50) butDRead = "PRESSED";
            else butDRead = "";
            return butDRead;
        }
};