#include <unistd.h>

class Camera {
	
	public:
		Camera(char* _save_dir);
		void start_recording();
		void stop_recording();
		bool is_recording();
		~Camera();
	private:
		char* save_dir;
		pid_t camera_pid;

		pid_t start_libcamera(char* filename);
		void stop_libcamera();
};
