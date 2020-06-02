#include "mbed.h"

Serial pc(USBTX, USBRX);
DigitalIn encoder(D11);

Ticker encoder_ticker;

volatile int steps;
volatile int last;

void encoder_control(void)
{
    // read the information(0 or 1) from pin
    int value = encoder;
    //  if last time is 0 and this time is 1, then will add one step
    //  which means that we have passed a hole!
    if (!last && value) 
	steps++;
    // update the last time value to this time
    last = value;
}

int main(void) 
{
    pc.baud(9600);
    pc.printf("Before start\r\n");

    // will call the funciton every 0.01s, that is, 10ms
    encoder_ticker.attach(&encoder_control, 0.01);

    steps = 0;
    last = 0;

    while(1) {
	// although the screen print the steps
	// every 2 second, it actaully sample the value
	// every 0.01 second!!
        wait(2);
        pc.printf("encoder = %d\r\n", steps);
    }
}
