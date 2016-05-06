#include "mbed.h"
#define pulse(theta) (700 + 10 * theta)
/* aaa */
PwmOut caderaRight(PA_3);
PwmOut piernaRight(PA_2);
PwmOut caderaLeft(PA_1);
PwmOut piernaLeft(PB_0);


DigitalOut myled(PB_1);

int main() {
    /*  */
    caderaRight.period(0.020);
    piernaRight.period(0.020);
    caderaLeft.pulsewidth(pulse(0));
    piernaLeft.pulsewidth(pulse(90));
    wait(2);
    int init = pulse(45);
    int backRight = pulse(45);
    int frontRight = pulse(135);
    int backLeft = pulse(135);
    int frontLeft = pulse(45);
    int upRight = pulse(90);
    int upLeft = pulse(90);
    int downRight = pulse(20);
    int downLeft = pulse(160);
    
    int fin = pulse(135);
    float tDelay = 0.2;
    
    while(1) {
        
        // (1) Left: D - B ; Right: U - F
        piernaLeft.pulsewidth_us(downLeft);
        caderaLeft.pulsewidth_us(backLeft);
        piernaRight.pulsewidth_us(upRight);
        caderaRight.pulsewidth_us(frontRight);
        wait(tDelay);
        // (2) Left: D - B ; Right: D - F
        piernaLeft.pulsewidth_us(downLeft);
        caderaLeft.pulsewidth_us(backLeft);
        piernaRight.pulsewidth_us(downRight);
        caderaRight.pulsewidth_us(frontRight);
        wait(tDelay);
        // (3) Left: U - B ; Right: D - F
        piernaLeft.pulsewidth_us(upLeft);
        caderaLeft.pulsewidth_us(backLeft);
        piernaRight.pulsewidth_us(downRight);
        caderaRight.pulsewidth_us(frontRight);
        wait(tDelay);
        // (4) Left: U - F ; Right: D - B
        piernaLeft.pulsewidth_us(upLeft);
        caderaLeft.pulsewidth_us(frontLeft);
        piernaRight.pulsewidth_us(downRight);
        caderaRight.pulsewidth_us(backRight);
        wait(tDelay);
        
        // (5) Left: D - F ; Right: D - B
        piernaLeft.pulsewidth_us(downLeft);
        caderaLeft.pulsewidth_us(frontLeft);
        piernaRight.pulsewidth_us(downRight);
        caderaRight.pulsewidth_us(backRight);
        wait(tDelay);
        
        // (6) Left: D - F ; Right: U - B
        piernaLeft.pulsewidth_us(downLeft);
        caderaLeft.pulsewidth_us(frontLeft);
        piernaRight.pulsewidth_us(upRight);
        caderaRight.pulsewidth_us(backRight);
        wait(tDelay);
        
        myled = 1;
    }
}
