#include "mbed.h"

Serial pc(USBTX, USBRX);
DigitalInOut ping(D11);
//  the pin can be used as input and output!
Timer t;

int main(void) 
{
    float val;
    pc.baud(9600);

    while(1) {
	// swith the mode to DigitalOut
        ping.output();
	// set the initial value to 0	
        ping = 0; wait_us(200);

	// send a start pulse to let the PING know
        ping = 1; wait_us(5);
        ping = 0; wait_us(5);
	
	// switch the mode to DigitalIn
        ping.input();
        
	while(ping.read()==0);
	// measure the time that it stay at 1
	// that is, the time that the wave
	// goes out then comes back 
        t.start();
        while(ping.read()==1);
        val = t.read();
	// since 2 * distance ==  speed * t
	// distance == (speed / 2) * t 
	//          == (344.8/2) *t * 100 cm(assume 22.2c)
	//          == 17240 * t
	printf("Ping = %lf\r\n", val*17240.0f);
        t.stop();
        t.reset();

        wait(1);
    }
}
