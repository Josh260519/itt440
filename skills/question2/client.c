#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>


int main() {
    char serverIP[16];
    int serverPort;
    int sock = 0, valread;
    int random_number;

    printf("Enter the server IP address: ");
    scanf("%s", serverIP);

    printf("Enter the server port number: ");
    scanf("%d", &serverPort);


    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation error");
        return -1;
    }

    // Set up server address
    
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    serverAddress.sin_addr.s_addr = inet_addr(serverIP);



    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("connection failed");
        return -1;
    }

    // Receive the random number from the server
    valread = read(sock, &random_number, sizeof(random_number));
    printf("Random number received from server: %d\n", random_number);

    return 0;
}
