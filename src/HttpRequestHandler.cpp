#include "HttpRequestHandler.h"

#include <iostream>

std::string HttpRequestHandler::handleRequest(const std::string& request) {
    std::cerr << "Request Line: " << request << std::endl;

    std::string response;
    std::string method = request.substr(0, request.find(" "));
    if (method == "GET") {
        std::string path = request.substr(request.find(" ") + 1);
        path = path.substr(0, path.find(" "));
        if (path == "/") {
            response = "HTTP/1.1 200 OK\r\n\r\n";
        } else if (path.find("/echo/") == 0) {
            std::string content = path.substr(6);
            response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: " + std::to_string(content.size()) + "\r\n\r\n" + content;
            if (content == "close") {
                return "HTTP/1.1 200 OK\r\n\r\n"; // Assuming you want to close the connection
            }
        } else {
            response = "HTTP/1.1 404 Not Found\r\n\r\n";
        }
    } else {
        response = "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
    }
    return response;
}
