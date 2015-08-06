#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void DieWithError(char *errMsg);

int AcceptTCPConnection(int servSock)
{
	int clntSock;
	struct sockaddr_in clntAddr;
	unsigned int clntLen;

	// Set size of the in-out parameter
	clntLen = sizeof(clntAddr);

	// Wait for a client to connect
	if((clntSock = accept(servSock, (struct sockaddr*) &clntAddr, &clntLen)) < 0)
		DieWithError("accept() failed!");

	// clntSock is connected to a client
	printf("Handling client %s\n", inet_ntoa(clntAddr.sin_addr));

	return clntSock; 
}

