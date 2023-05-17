#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h> //inet_addr

int main(int argc, char *argv[])
{
	int socket_desc , new_socket, c;
	struct sockaddr_in server, client;
	char *message;
	char server_reply[2000];

	//Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	//Preparing the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(12345);

	//Binding
	if (bind(socket_desc,(struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("Bind failed");
	}
	puts("Bind done");

	//Listen
	listen(socket_desc, 3);

	//Accept any incoming connection
	puts("Waiting for incoming connections...");


	while (1)
	{
	//Accept a connection
	int c = sizeof(struct sockaddr_in);
	new_socket = (accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c));
	if (new_socket < 0)
	{
		puts("Accept failed");
		return 1;
	}
	puts("Connection accepted");

	// Create a child process to handle the connection
        pid_t pid = fork();
        if (pid == 0)
        {
            // Child process

            // Close the listening socket in the child process
            close(socket_desc);

            // Send some data
            message = "Server";
            if (send(new_socket, message, strlen(message), 0) < 0)
            {
                puts("Send failed");
                return 1;
            }
            puts("Data sent\n");

            // Receive a reply from the client
            if (recv(new_socket, server_reply, 2000, 0) < 0)
            {
                puts("Receive failed");
                return 1;
            }

            puts("Client reply received:");
            puts(server_reply);

            // Close the connection
            if (close(new_socket) < 0)
            {
                puts("Error closing the socket");
                return 1;
            }
            puts("Connection closed");

            // Exit the child process
            return 0;
        }
        else if (pid < 0)
        {
            puts("Fork failed");
            return 1;
        }

        // Parent process
        // Close the new_socket in the parent process to allow it to accept more connections
        close(new_socket);
    }

    return 0;
}


