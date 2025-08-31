# Simple HTTP Server and Client

A minimal implementation of an HTTP **server** and **client** written in C.  
This project was created for educational purposes, to better understand how HTTP requests and responses work at a low level using sockets.

## Files

- `http_server.c` → Handles basic HTTP requests and serves static responses.  
- `http_client.c` → Connects to a server and sends HTTP requests.

## Compilation

- `gcc server.c -o server`
- `gcc client.c -o client`

## Usage

- `./server`
- `./client <IP> <PORT>`
