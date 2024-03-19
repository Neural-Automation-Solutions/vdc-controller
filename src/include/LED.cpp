#include "LED.h"
#include <pigpio.h>
#include <cstdio>

LED::LED(unsigned int _pin) {
	pin = _pin;

	// multiple initializations are fine
	if (gpioInitialise() == PI_INIT_FAILED) {
		printf("ERROR: Failed to initialize GPIO interface.\n");
	}

	gpioSetMode(pin, PI_OUTPUT);
}

LED::~LED() {
	off();
	gpioSetMode(pin, PI_INPUT);
	gpioTerminate();
}

void LED::on() {
	gpioWrite(pin, PI_HIGH);
}

void LED::off() {
	gpioWrite(pin, PI_LOW);
}
