class Timer {
    public:
        Timer(long milliseconds);
        long getTime();
        boolean check();

        boolean Timer::check(){
        this->frame = millis() - this->timeSinceStart;
        this->timeSinceStart = millis();
    if(this->iteratorTime>this->waitingTime){
        this->iteratorTime = 0;
        return true;
    } else {
        this->iteratorTime += this->frame;
        return false;
    }
};
