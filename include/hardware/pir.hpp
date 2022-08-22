 #include <Arduino.h>
#define PIRPIN 2

class PIR
{
    public:
        PIR();
        ~PIR();
        int run();
    private:
        int state;
        int val;
};