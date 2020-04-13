#include <iostream>
#include <ctime>
#include <cstdlib>

#include <Windows.h>

int main() {
	STARTUPINFO startUpInfo;
	PROCESS_INFORMATION processInfo;
	
	ZeroMemory(&startUpInfo, sizeof(startUpInfo));
	ZeroMemory(&processInfo, sizeof(processInfo));

	startUpInfo.cb = sizeof(startUpInfo); // What the fuck?
	wchar_t command[] = L"Child.exe";

	bool handleCreated = CreateProcess(
		/* Application name */	NULL,
		/* Command line */		command,
		/* Process Attrs */		NULL,
		/* Security Attrs */	NULL,
		/* Inherit handler */	FALSE,
		/* Creation flags */	CREATE_NEW_CONSOLE,
		/* Enviroment */		NULL,
		/* Current directory */	NULL,
		/* Startup info */		&startUpInfo,
		/* Process info */		&processInfo
	);

	if (!handleCreated) {
		std::cout << "Couldn't create new handle for process!"
			<< std::endl << GetLastError()
			<< std::endl;
		std::cin.get();
		return -1;
	}

	for (int i = 0; i < 5; i++) {
		std::time_t t = std::time(0);
		std::tm* now = new std::tm;
		localtime_s(now, &t);
		std::cout << now->tm_hour << ":"
			<< now->tm_min << ":"
			<< now->tm_sec << std::endl;
		Sleep(1000);
	}

	std::cout << "Waiting for child to finish" << std::endl;

	WaitForSingleObject(processInfo.hProcess, INFINITE);

	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);

	std::cout << "Parent finish!" << std::endl;
	std::cin.get();
	return 0;
}