#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 4455
#define CLIENTPORT 9988


void main(){
	int clientSocket;
	struct sockaddr_in clientAddr;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&clientAddr, '\0', sizeof(clientAddr));

	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = CLIENTPORT;
	clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(clientSocket, (struct sockaddr*)&clientAddr, sizeof(clientAddr));



	printf("[+]Client Socket Created Succefully with port number %d\n", CLIENTPORT );


	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("[+]Connected to the server successfully\n");

	while(1)
	{
		recv(clientSocket, buffer, 1024, 0);
		if(!strcmp(buffer,"quit\n"))
		{
			printf("[+]Closing the client\n");
			break;
		}
		printf("Data recieved: %s", buffer);
		memset(buffer, '\0', sizeof(buffer));
	}
	exit(0);
}
