#include <iostream>
#include <ctime>
#include <cstring>

char* get_filename() {
	std::time_t currentTime = std::time(nullptr);
	char* timeString = std::ctime(&currentTime);

	for (size_t i=0; i<strlen(timeString); ++i) {
		if (timeString[i] == ' ' || timeString[i] == '\n')
			timeString[i] = '-';
	}

	return timeString;
}
