# Client-Server Communication in C

This project demonstrates the basic principle of **client-server communication** using **sockets** in the C programming language.  
The server and client establish a connection over TCP (Transmission Control Protocol).

## Program Description

- **server.c** – creates a socket, listens on a specified port, and waits for a client connection. After receiving a message, it can process it and send a response back to the client.  
- **client.c** – creates a socket, connects to the server, and sends it a message (e.g., a text string). It then waits for the server’s response.

The programs demonstrate the principles of:
- creating and closing sockets,
- using the functions `bind()`, `listen()`, `accept()`, `connect()`, `send()`, and `recv()`,
- basic bidirectional communication over a network.<br><br>

Author: Denis Čumitta
