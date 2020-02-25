#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 4455
#define NEWPORT 1598


void main(){
	int sockfd;
	struct sockaddr_in serverAddr;
	
	int newSocket;
	struct sockaddr_in newAddr;

	struct sockaddr_in clientAddr;

	socklen_t addr_size;
	char buffer[1024];

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	printf("[+]Server listening socket created succefully\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("[+]Bind to the port number %d\n", PORT);


	newAddr.sin_port = NEWPORT;
	bind(newSocket, (struct sockaddr*)&newAddr, sizeof(newAddr));

	listen(sockfd, 1);
	printf("[+]Listening...\n");

	addr_size = sizeof(clientAddr);
	newSocket = accept(sockfd, (struct sockaddr*)&clientAddr, &addr_size);

	printf("[+]Connected to the client successfully\n");
	printf("[+]Created new socket to send data with port number %d\n", newAddr.sin_port);
	printf("[+]Type data you want to send\n");
	printf("[+]Type 'quit' to exit\n");
	while(1)
	{
		memset(buffer, '\0', sizeof(buffer));
		fgets(buffer, 1024, stdin);
		send(newSocket, buffer, strlen(buffer), 0);

		if(!strcmp(buffer,"quit\n"))
		{
			printf("[+]Closing the server\n");
			break;
		}
	}
	exit(0);


}
