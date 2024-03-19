#include <iostream>
#include "Camera.h"
#include "utils.h"

using namespace std;

int main () {

	Camera cam("./data");
	cam.start_recording();

	sleep(3);
	
	for (;;) {
		// do nothing
	}

	//cout << get_filename() << endl;

	return 0;
}
