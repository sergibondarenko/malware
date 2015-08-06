#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define MAXPENDING 5					// Max outstanding connection req

void DieWithError(char *errMsg);

int CreateTCPServerSocket(unsigned short port)
{
	int sock;
	struct sockaddr_in servAddr;

	// Create socket for incomming connection
	if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("socket() failed!");
	
	// Construct local addr structure
	memset(&servAddr, 0, sizeof(servAddr));			// Zero out structure
	servAddr.sin_family = AF_INET;						// Internet addr family
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	// Any incomming interface
	servAddr.sin_port = htons(port);						//	Local port

	// Bind to local addr
	if(bind(sock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0)
		DieWithError("bind() failed!");

	// Mark the socket to listen for incomming connections
	if(listen(sock, MAXPENDING) < 0)
		DieWithError("listen() failed!");

	return sock;
}

