#include <stdio.h>
#include <conio.h>
#include "UDPDriver.h"

int main() {
	int socketPort = 54007;
	char serverIP[] = "192.168.0.119"; // "192.168.1.157"; PC as a Server  
	char clientIP[] = "192.168.0.188"; // "192.168.1.116"; Mona Robot as a Client 
	// char serverIP[] = "192.168.0.188"; // "192.168.1.157"; PC as a Server  
	// char clientIP[] = "192.168.0.119"; // "192.168.1.116"; Mona Robot as a Client 
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