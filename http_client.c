#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char * argv[]){
    
    char *address = NULL;
    int port = 0;

    address = argv[1];
    port = atoi(argv[2]);

    // Socket
    int clientSocket = 0;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Remote Address
    struct sockaddr_in serverAddress = {0};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    inet_pton(AF_INET, address, &(serverAddress.sin_addr)); // Converting Address

    connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    char request[] = "GET / HTTP/1.1\r\n\r\n";
    char response[4096] = {0};

    send(clientSocket, request, sizeof(request), 0);
    recv(clientSocket, &response, sizeof(response), 0);

    printf("[SERVER]: %s\n", response);

    close(clientSocket);
    
    return 0;
}
