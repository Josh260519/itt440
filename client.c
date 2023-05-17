#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>  //inet_addr
#include <string.h>


int main(int argc, char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	char *message;
	char server_reply[2000];

	// Creating socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	server.sin_addr.s_addr = inet_addr("192.168.17.128"); //ip of host
	server.sin_family = AF_INET;
	server.sin_port = htons(12345);


	//Connecting to server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("Connect error");
		return 1;
	}
	puts("Connected\n");

	//Send data
	message = "client";

	if ( send(socket_desc, message, strlen(message) ,0 ) <0)
	{
		puts("Send Failed");
		return 1;
	}

	puts("Data Send\n");
	//Receive a reply from the server

	if ( recv(socket_desc, server_reply, 2000, 0) <0)
	{
		puts("Receive Failed");
		return 1;
	}

	puts("Received server reply\n");
	puts(server_reply);

	if (close(socket_desc) < 0)
	{
		puts("Error closing the socket\n");
		return 1;
	}
	puts("Connection closed");
	return 0;
}
