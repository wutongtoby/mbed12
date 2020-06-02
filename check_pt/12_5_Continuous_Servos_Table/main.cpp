#include "mbed.h"

#define CENTER_BASE 1500

Serial pc(USBTX, USBRX);
DigitalIn encoder(D10);
PwmOut servo(D11);

Timer t;
Ticker encoder_ticker;

volatile int steps;
volatile int last;

void servo_control(int speed)
{
    if (speed > 200)       
        speed = 200;
    else if (speed < -200) 
        speed = -200;

    servo = (CENTER_BASE + speed) / 20000.0f;
}

void encoder_control(void)
{
    int value = encoder;
    
    if(!last && value) 
        steps++;
    
    last = value;
}

int main(void) 
{
    pc.baud(9600);
    encoder_ticker.attach(&encoder_control, 0.001);
    
    // set the duty cycle
    servo.period(0.02);
    int i = 0;
    
    while(i <= 150) {
	// set a specific speed 
        servo_control(-i);

	// reset the steps parameter 
        steps = 0;

        t.reset();
        t.start();

        wait(8);

        float time = t.read();
	//float speed = (steps / 32.0) * (6.5 * 3.14) / time;
	// steps / 32 = number of turns
	// 6.5 * 3.14 = 2 * pi * r
    pc.printf("%1.3f\r\n", (float)steps*6.5*3.14/32/time);


        i += 30;
    }
    servo_control(0);

    while(1);
}
