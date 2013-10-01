//============================================================================
// Name        : TestServer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "Configuration.h"
#include "Status.h"


void* SocketHandler(void*);

Configuration myConfig;
Status myStatus;

int main(int argc, char *argv[]){

	int host_port= 1101;

	struct sockaddr_in my_addr;

	int hsock;
	int * p_int ;

	socklen_t addr_size = 0;
	int* csock;
	sockaddr_in sadr;
	pthread_t thread_id=0;

    if (argc == 2) {
    	host_port = atoi(argv[1]);
    }
	printf("host Port  %d\n", host_port);
    myConfig.ReadFile();

    char XMLString[4096];

    myConfig.XMLStream(XMLString);

    //printf("Configuration from file: \n %s", XMLString);



	hsock = socket(AF_INET, SOCK_STREAM, 0);
	if(hsock == -1){
		printf("Error initializing socket %d\n", errno);
		goto FINISH;
	}

	p_int = (int*)malloc(sizeof(int));
	*p_int = 1;

	if( (setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
		(setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) ){
		printf("Error setting options %d\n", errno);
		free(p_int);
		goto FINISH;
	}
	free(p_int);

	my_addr.sin_family = AF_INET ;
	my_addr.sin_port = htons(host_port);

	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = INADDR_ANY ;

	if( bind( hsock, (sockaddr*)&my_addr, sizeof(my_addr)) == -1 ){
		printf("Error binding to socket, make sure nothing else is listening on this port %d\n",errno);
		goto FINISH;
	}
	if(listen( hsock, 10) == -1 ){
		printf("Error listening %d\n",errno);
		goto FINISH;
	}

	//Now lets do the server stuff

	addr_size = sizeof(sockaddr_in);

	while(true){
		printf("waiting for a connection on port %d\n", host_port);
		csock = (int*)malloc(sizeof(int));
		if((*csock = accept( hsock, (sockaddr*)&sadr, &addr_size))!= -1){
			printf("---------------------\nReceived connection from %s\n",inet_ntoa(sadr.sin_addr));
			pthread_create(&thread_id,0,&SocketHandler, (void*)csock );
			pthread_detach(thread_id);
		}
		else{
			printf("Error accepting %d\n", errno);
		}
	}

FINISH:
;
}

void* SocketHandler(void* lp){
    int *csock = (int*)lp;

	char* buffer = new char[4096];
	int buffer_len = 4096;
	int bytecount;

	while(1)
	{
		memset(buffer, 0, buffer_len);
		if((bytecount = recv(*csock, buffer, buffer_len, 0))== -1){
			printf("Error receiving data %d\n", errno);
			goto FINISH;
		}
		printf("Received bytes %d\nReceived string %s\n", bytecount, buffer);
		if(bytecount == 0) {
			goto FINISH;
		}

		if(!strncmp("<Configuration>",buffer,15))
		{
			//read the string in and update the configuration
			myConfig.ProcessXMLStream(buffer);
			//Print the xml data

			myConfig.SaveFile();
		}
		else if (!strncmp("<GetConfig>",buffer,11))
		{
			//printf("Request Configuration Data from webpage\n");

			myConfig.XMLStream(buffer);

			if((bytecount = send(*csock, buffer, strlen(buffer), 0))== -1){
						printf("Error sending data %d\n", errno);
						goto FINISH;
					}

			//printf("Sent bytes %d\n", bytecount);
		}
		else if (!strncmp("<GetStatus>",buffer,11))
		{
			//printf("Request Status Data from webpage\n");

			myStatus.XMLStream(buffer);

			if((bytecount = send(*csock, buffer, strlen(buffer), 0))== -1){
						printf("Error sending data %d\n", errno);
						goto FINISH;
					}

			//printf("Sent bytes %d\n", bytecount);
		}
		else if (!strncmp("<Gains>",buffer,7))
		{
			printf("Update gains from webpage\n");

			//read the string in and update the configuration
			myConfig.ProcessXMLStream(buffer);
			//Print the xml data

			myConfig.SaveFile();

		}
		else if (!strncmp("Action:",buffer,7))
		{
			printf("Button pressed on webpage\n");
			const char* Command[] =
			{
					"Action:Reset-Counts",
					"Action:Restart-App",
					"Action:Reboot"
			};
			{
				int i = 0;
				while ((i<3) && strcmp(buffer,Command[i]))i++;
				printf("Button pressed on webpage: Do Action %d\n", i);
			}

			//Need to reboot or restart etc depending on the string

		}
	}


FINISH:
	//shutdown(*csock, SHUT_RDWR);
	close(*csock);
	free(csock);
	free(buffer);
    return 0;
}
