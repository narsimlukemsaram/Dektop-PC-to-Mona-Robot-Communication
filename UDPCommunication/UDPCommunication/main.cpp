#include <stdio.h>
#include <conio.h>
#include "UDPDriver.h"

int main() {
	int socketPort = 54007;
	char serverIP[] = "serverIP"; // PC as a Server  
	char clientIP[] = "clientIP"; // Mona Robot as a Client 
	UDPDriver driver;
	driver.initialise(serverIP, socketPort, clientIP);

	printf("Press any key to send a command\n");
	printf("(Press 'q' to quit the program)\n");
	bool finished = false;
	while (!finished) {
		if (_kbhit()) {
			char c = _getch();
			driver.sendByte(c);
			// printf("Sent a string");
			printf("Sent a command '%c'\n", c);
			if (c == 'q') finished = true;
		}
	}

	driver.disconnect();
	return 0;
}
