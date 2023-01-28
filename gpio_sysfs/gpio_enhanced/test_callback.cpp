#include<iostream>
#include<unistd.h>
#include"../gpio_sysfs/GPIO.h"

using namespace exploringRPi;
using namespace std;

GPIO *pin_in, *pin_out;

int activateLED(int var){
    pin_out->streamWrite(HIGH);
    cout << "Button Pressed" << endl;
    return 0;
}

int main(){
    pin_in = new GPIO(27);
    pin_out = new GPIO(17);
    pin_in->setDirection(INPUT);
    pin_out->setDirection(OUTPUT);
    pin_out->streamOpen();
    pin_out->streamWrite(LOW);
    pin_in->setEdgeType(RISING);
    cout << "You have 10 seconds to press the button: " << endl;
    pin_in->waitForEdge(&activateLED);
    cout << "Listening, but also doing something else..." << endl;
    for(int i=0; i<10; i++){
        usleep(1000000);        
        cout << "[sec]" << flush;   
    }
    pin_out->streamWrite(LOW);     
    pin_out->streamClose();        
    return 0;
}