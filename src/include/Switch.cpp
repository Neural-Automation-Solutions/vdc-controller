#include "Switch.h"
#include <pigpio.h>
#include <cstdio>
#include <unistd.h>
#include <csignal>
#include <cstdio>

Switch::Switch(unsigned int _pin) {
	pin = _pin;

	if (gpioInitialise() == PI_INIT_FAILED) {
		printf("ERROR: Failed to initialize GPIO interface.\n");
	}

	gpioSetMode(pin, PI_INPUT);

	// set alert function whenever GPIO changes state
	if (gpioSetAlertFunc(pin, callbackFunc) != 0) {
		printf("ERROR: Failed to set callback function.\n");
		gpioTerminate();
	}
}

int Switch::getState() {
	// read gpio
	return gpioRead(pin);
}

Switch::~Switch() {
	gpioInitialise();
	gpioTerminate();
}

void Switch::callbackFunc(int gpio, int level, unsigned int tick) {

	printf("gpio: %d, level: %d, tick: %d\n", gpio, level, tick);

	// send SIGUSR1 signal to self
	kill(getpid(), SIGUSR1);

}
