#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <arpa/inet.h>

int main(){
    
    // Open file HTLM file to serve.
    FILE * htmlData;
    htmlData = fopen("index.html", "r");

    char responseData[1024] = {0}; 
    fgets(responseData, 1024, htmlData);

    char httpHeader[2048] = "HTTP/1.1 200 OK\r\n\n";
    strncat(httpHeader, responseData, sizeof(responseData));

    // TCP Socket
    int serverSocket = 0;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1){
        printf("Something went wrong when creating the socket.\n");
        perror("socket");
    }
    
    // Building serverAddr structure.
    struct sockaddr_in serverAddr = {0};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Change this to 80 eventually.
    inet_pton(AF_INET, "0.0.0.0", &(serverAddr.sin_addr));

    // Binding name to a socket.
    int bindSocket = 0;
    bindSocket = bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (bindSocket == -1){
        printf("Something went wrong when binding the socket.\n");
        perror("bind");
    }
    
    // Listening for connections
    int listenConn = 0;
    listenConn = listen(serverSocket, 1);
    if (listenConn != 0){
        printf("Something went wrong when listening for connections\n");
        perror("listen");
    }
    
    // Accept the connection in queue.
    int clientSocket = 0;
    struct sockaddr clientAddress = {0};
    int clientAddressLength = sizeof(clientAddress);

    // Here we build the part where the server enters in an infinite loop state, to answer client requests
    
    while (true){
        clientSocket = accept(serverSocket, &clientAddress, &clientAddressLength);
        if (clientSocket == -1){
            printf("Something went wrong when accepting the connection from the client\n");
            perror("accept");
            break;
        }
        
        send(clientSocket, httpHeader, sizeof(httpHeader), 0);
        close(clientSocket);
    }

    return 0;
}
