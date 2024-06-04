#include <iostream>     // Includes standard input-output stream library
#include <cstdlib>      // Includes standard library for general utilities
#include <string>       // Includes string class for string manipulation
#include <cstring>      // Includes functions for C-style string handling
#include <unistd.h>     // Includes POSIX operating system API
#include <sys/types.h>  // Includes definitions of data types used in system calls
#include <sys/socket.h> // Includes definitions of socket functions and data structures
#include <arpa/inet.h>  // Includes definitions for internet operations
#include <netdb.h>      // Includes definitions for network database operations

int main(int argc, char **argv)
{
    // Flush std::cout and std::cerr buffers after every output operation
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // Debugging statement, prints logs to console
    std::cout << "Logs from your program will appear here!\n";

    while(1){
    // Create a socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        std::cerr << "Failed to create server socket\n";
        return 1;
    }

    // Set socket options to reuse the address
    int reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
    {
        std::cerr << "setsockopt failed\n";
        return 1;
    }

    // Define server address structure
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;              // Address family: Internet
    server_addr.sin_addr.s_addr = INADDR_ANY;      // Accept connections from any IP address
    server_addr.sin_port = htons(4221);            // Set port number, converted to network byte order

    // Bind the socket to the specified port and address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0)
    {
        std::cerr << "Failed to bind to port 4221\n";
        return 1;
    }

    // Set the socket to listen for incoming connections
    int connection_backlog = 5; // Maximum length for the queue of pending connections
    if (listen(server_fd, connection_backlog) != 0)
    {
        std::cerr << "listen failed\n";
        return 1;
    }

    // Define client address structure for accepting connections
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    std::cout << "Waiting for a client to connect...\n";

    // Accept a connection from a client
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);
    if (client_fd < 0)
    {
        std::cerr << "error handling client connection\n";
        close(server_fd); // Close server socket
        return 1;
    }
    std::cout << "Client connected\n";

    // Receive a message from the client
    std::string client_message(1024, '\0'); // Allocate buffer for message
    ssize_t brecvd = recv(client_fd, (void *)&client_message[0], client_message.max_size(), 0);
    if (brecvd < 0)
    {
        std::cerr << "error receiving message from client\n";
        close(client_fd);   // Close client socket
        close(server_fd);   // Close server socket
        return 1;
    }

    // Log received message
    std::cerr << "Client Message (length: " << client_message.size() << ")" << std::endl;
    std::clog << client_message << std::endl;

    // Parse the request line to determine if it's an /echo/{str} request
    std::string request_line = client_message.substr(0, client_message.find("\r\n"));
    std::cerr << "Request Line: " << request_line << std::endl;

    std::string response;
    std::string method = request_line.substr(0, request_line.find(" "));
    if (method == "GET")
    {
        std::string path = request_line.substr(request_line.find(" ") + 1);
        path = path.substr(0, path.find(" "));
        if(path=="/"){
            response = "HTTP/1.1 200 OK\r\n\r\n";
        }
        else if (path.find("/echo/") == 0)
        {
             std::string content = path.substr(6);
            response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: " + std::to_string(content.size()) + "\r\n\r\n" + content;
            if(content == "close"){
              return 0;
            }
        }
        else
        {
            response = "HTTP/1.1 404 Not Found\r\n\r\n";
        }
    }
    else
    {
        response = "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
    }

    // Send the response to the client
    ssize_t bsent = send(client_fd, response.c_str(), response.size(), 0);
    if (bsent < 0)
    {
        std::cerr << "error sending response to client\n";
        close(client_fd);   // Close client socket
        close(server_fd);   // Close server socket
        return 1;
    }
    close(client_fd);
    close(server_fd);
    }
    // Close the client and server sockets
    return 0;
}
