#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>	// for sockaddr_in and inet_ntoa()
#include <stdlib.h>		// for atoi()
#include <string.h>		//	for memset
#include <unistd.h>		//	for clode()
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>


void DieWitError(char *errMSG);						// Error handling function
void HandleTCPClient(int clntSocket);				// TCP client handling 
void HandleTCPClientFull(int clntSocket);				// TCP client handling 
int CreateTCPServerSocket(unsigned short port);	// Create TCP server socket 
int AcceptTCPConnection(int servSock);				// Accept TCP connection req
