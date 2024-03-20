#include <iostream>
#include <csignal>

#include "Camera.h"
#include "LED.h"
#include "Switch.h"
#include "utils.h"

// configuration

#define SAVE_DIR "/home/yiannis/vdc-controller/data"

using namespace std;

// Camera
Camera cam(SAVE_DIR);

// LEDs
// LED showing program status (on: running, off: not running)
LED programStatusLED(17);
// LED showing camera status (on: recording, off: not recording)
LED cameraStatusLED(4);

// Switch
Switch s(2);
bool switchState = s.getState();

// stop and exit process if true
bool sigintReceived = false;

void sigUsr_handler(int sig) {
	std::cout << "signal: " << sig << std::endl;
	
	// update switch state
	// reading the gpio value everytime ensures that no matter what
	// happens (in software or hardware), switchState will always
	// match the state of the set GPIO pin
	switchState = s.getState();

	// switchState == 1
	if (switchState) {
		// turn on camera
		cam.start_recording();
	}
	// switchState == 0
	else {
		// turn off camera
		// waiting for the libcamera-vid process to end is handled
		// by Camera
		cam.stop_recording();

	}

	// update cameraStatusLED based on Camera reading
	// ensures that the cameraStatusLED will turn on
	// only when the camera is truly recording
	if (cam.is_recording()) cameraStatusLED.on();
	else cameraStatusLED.off();
}

void sigInt_handler(int sig) {
	sigintReceived = true;
}

int main () {

	std::cout << "switchState: " << switchState << std::endl;

	// switch sends a SIGUSR1 whenever the switch state changes
	signal(SIGUSR1, sigUsr_handler);

	// use SIGINT (CTRL+C) to kill the parent process
	signal(SIGINT, sigInt_handler);

	// turn program status LED on
	programStatusLED.on();

	// if initial switchState is 1 (on) then turn on camera
	if (switchState) {
		cam.start_recording();

		// update cameraStatusLED
		cameraStatusLED.on();
	}

	while (!sigintReceived) {
		// do nothing
	}

	programStatusLED.off();

	return 0;
}
