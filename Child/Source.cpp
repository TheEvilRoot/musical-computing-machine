#include <iostream>
#include <ctime>
#include <cstdlib>

#include <Windows.h>

int main() {
	for (int i = 0; i < 10; i++) {
		std::time_t t = std::time(0);
		std::tm* now = new std::tm;
		localtime_s(now, &t);
		std::cout << now->tm_hour << ":"
			<< now->tm_min << ":"
			<< now->tm_sec << std::endl;
		Sleep(1000);
	}
	std::cout << "Child finish!" << std::endl;
	return 0;
}