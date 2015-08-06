#include "lib/TCPServer.h"
#include <pthread.h>

void *ThreadMainRoutine(void *arg);			// Main program of thread

struct ThreadArgs							// Structure of args to pass to client thread 
{
	int clntSock;
};

int main(int argc, char *argv[])
{
	int servSock, clntSock;				// Sockets descriptors
	unsigned	short servPort;		// Server port
	pthread_t threadID;					// Thread ID
	struct ThreadArgs *threadArgs;

	if(argc != 2){							// Test for correct number of args
		fprintf(stderr, "Usage %s <Server Port>\n", argv[0]);
		exit(1);
	}

	servPort = atoi(argv[1]);

	servSock = CreateTCPServerSocket(servPort);

	for(;;){
		clntSock = AcceptTCPConnection(servSock);

		// Create separate memory for client arg
		if((threadArgs = (struct ThreadArgs*) malloc(sizeof(struct ThreadArgs))) == NULL)
			DieWithError("malloc() failed!");
		threadArgs -> clntSock = clntSock;

		// Create client thread
		if(pthread_create(&threadID, NULL, ThreadMainRoutine, (void *) threadArgs) != 0)
			DieWithError("pthread_create() failed!");

		printf("with thread %ld\n", (long int) threadID);
	}
}

void *ThreadMainRoutine(void *threadArgs)
{
	int clntSock;
	
	// Thread resources are deallocated upon return
	pthread_detach(pthread_self());
	
	//	Extract socket descriptor from arg
	clntSock = ((struct ThreadArgs*) threadArgs) -> clntSock;
	free(threadArgs);

	HandleTCPClient(clntSock);

	return (NULL);
}
