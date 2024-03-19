#include <iostream>
#include "Camera.h"
#include "utils.h"

using namespace std;

int main () {

	Camera cam("./data");
	cam.start_recording();

	sleep(5);

	cam.stop_recording();

	//for (;;) {
		// do nothing
	//}

	//cout << get_filename() << endl;

	return 0;
}
