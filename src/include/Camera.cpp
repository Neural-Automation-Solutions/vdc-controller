#include "Camera.h"
#include "utils.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <csignal>
#include <cstdlib>

Camera::Camera(char* _save_dir) {
	save_dir = _save_dir;
	camera_pid = 0;
}

Camera::~Camera() {
	stop_recording();
}

void Camera::start_recording() {
	char* filename = get_filename();
	camera_pid = start_libcamera(filename);
}

void Camera::stop_recording() {
	stop_libcamera();	
}

bool Camera::is_recording() {
	return system("pgrep -x 'libcamera-vid'") == 0;
}

pid_t Camera::start_libcamera(char* filename) {
	
	// create output file path
	char name[100];
	sprintf(name, "%s/%s.mp4", save_dir, filename);

	std::cout << name << std::endl;

	//return 0;

	// create child process
	pid_t child = fork();

	if (child == 0) {
		execl("/usr/bin/libcamera-vid",
			// bitrate - 9000000 is suggested for less artifacts
			// but I couldn't get better results than the default
			// no matter what bitrate I used
			// "-b",
			// "9000000",
			"--framerate",
			"30",
			// timeout - set to 0 so it doesn't stop unless we say so
			"-t",
			"0",
			// codec for mp4 output
			"--codec",
			"libav",
			// resolution - 1920x1080 for HD
			// "--width",
			// "1920",
			// "--height",
			// "1080",
			// enable signals
			"-s",
			// output
			"-o",
			name,
			NULL);

	}

	return child;
}

void Camera::stop_libcamera() {
	if (camera_pid) {
		// libcamera-vid built-in functionality
		// quits on SIGUSR2
		kill(camera_pid, SIGUSR2);
	}

	// wait for libcamera-vid process to stop
	int status;
	waitpid(camera_pid, &status, 0);

	camera_pid = 0;
}
