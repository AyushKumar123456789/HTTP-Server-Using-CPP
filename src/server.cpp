#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include "HttpRequestHandler.h"
#include <thread>


int HandleRequest(  struct sockaddr_in client_addr,socklen_t client_addr_len,int server_fd)
{
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
        // Accept is blocking system call
        if (client_fd < 0) {
            std::cerr << "error handling client connection\n";
            close(server_fd); // Close server socket
            return 1;
        }
        std::cout << "Client connected\n";

        // Receive a message from the client
        std::string client_message(1024, '\0'); // Allocate buffer for message
        ssize_t brecvd = recv(client_fd, &client_message[0], client_message.size(), 0);
        // Recv is blocking system call
        if (brecvd < 0) {
            std::cerr << "error receiving message from client\n";
            close(client_fd);   // Close client socket
            close(server_fd);   // Close server socket
            return 1;
        }

        // Handle the HTTP request using HttpRequestHandler
        std::string response = HttpRequestHandler::handleRequest(client_message);

        // Send the response to the client
        ssize_t bsent = send(client_fd, response.c_str(), response.size(), 0);
        if (bsent < 0) {
            std::cerr << "error sending response to client\n";
            close(client_fd);
            close(server_fd);
            return 1;
        }
        close(client_fd);
        return 1;
}

int main(int argc, char **argv) {
    // Flush std::cout and std::cerr buffers after every output operation
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // Debugging statement, prints logs to console
    std::cout << "Logs from your program will appear here!\n";

        // Create a socket
        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) {
            std::cerr << "Failed to create server socket\n";
            return 1;
        }

        // Set socket options to reuse the address
        int reuse = 1;
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
            std::cerr << "setsockopt failed\n";
            return 1;
        }

        // Define server address structure
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;              // Address family: Internet
        server_addr.sin_addr.s_addr = INADDR_ANY;      // Accept connections from any IP address
        server_addr.sin_port = htons(4221);            // Set port number, converted to network byte order

        // Bind the socket to the specified port and address
        if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
            std::cerr << "Failed to bind to port 4221\n";
            return 1;
        }

        // Set the socket to listen for incoming connections
        int connection_backlog = 5; // Maximum length for the queue of pending connections
        if (listen(server_fd, connection_backlog) != 0) {
            std::cerr << "listen failed\n";
            return 1;
        }

        // Define client address structure for accepting connections
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        
    while(1) {
        std::cout << "Waiting for a client to connect...\n";

        // Accept a connection from a client
        std::thread th (HandleRequest,  client_addr,client_addr_len,server_fd);
        th.join();

    }
        close(server_fd);

    // Close the client and server sockets if needed
    return 0;
}
