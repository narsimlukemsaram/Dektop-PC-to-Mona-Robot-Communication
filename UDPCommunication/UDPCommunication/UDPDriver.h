#ifndef _ASIERINHO_UDP_DRIVER
#define _ASIERINHO_UDP_DRIVER

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <windows.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib") //obj comment to link winsock to the executable 

/**
	Class for SPI connection
*/
class UDPDriver {
	char* serverIP;			//this is your servers IP address, aka this computers IP (wherever runtime is)
	int socketPort;			//this socket will be reserved for your communication, if you can't bind to it during runtime, then try a different socket
	char* clientIP;			//this is the IP address of your clinet. the last part should be 255 if using broadcast address 
	bool isClientSet;
	SOCKET serverSocket;
	sockaddr_in serverAddr;

	enum DriverStates { INIT = 0, READY, ENDED, ERRORS };
	int status;
public:
	static const int MAX_MESSAGE_SIZE = 1460;

	UDPDriver();

	void initialise(char* serverIP, int socketPort, char* clientIP = NULL);
	void setClient(char* clientIP);
	void sendString(unsigned char* buffer, int numBytes);
	void sendByte(unsigned char byte);
	bool anyErrors();
	void disconnect();

private:
	bool begin();
	bool bindServer();
	void cleanup();
};

#endif