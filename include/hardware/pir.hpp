 #include <Arduino.h>
#define PIRPIN 2

class PIR
{
    public:
        PIR();
        ~PIR();
        void run();
        int getState(){return state;};
    private:
        int state;
        int val;
};