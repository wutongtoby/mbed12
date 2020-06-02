#include "mbed.h"

#define CENTER_BASE 1500

PwmOut servo(D11);
// the float number assigned on PWNout means the duty cycle

void servo_control(int speed) {
    if (speed > 200)
        speed = 200;
    else if (speed < -200)
        speed = -200;
    servo = (CENTER_BASE + speed) / 20000.0f;
    // if duty cycle > 1500 / 20000, rotate counter-clockwisely.
    // if duty cycle < 1500 / 20000, rotate clockwisely.
    // if duty cycle == 1500 / 20000, stop!
}

int main() {
    servo.period(.02);
    // so the inital duty cycle will be 20%
    
    while(1) {
        servo_control(0.0);
        wait(2);
        servo_control(0.0);
        wait(2);
    }
}
