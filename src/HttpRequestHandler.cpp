#include "HttpRequestHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define FILES_DIRECTORY "../files"

std::string readFileContents(const std::string& filename) {
    std::ifstream file(std::string(FILES_DIRECTORY) + "/" + filename, std::ios::binary);
    if (file) {
        std::ostringstream contentStream;
        contentStream << file.rdbuf();
        file.close();
        return contentStream.str();
    } else {
        return "";
    }
}

std::string HttpRequestHandler::handleRequest(const std::string& request) {
    std::cerr << "Request Line: " << request << std::endl;

    std::string response;
    std::string method = request.substr(0, request.find(" "));

    if (method == "GET") {
        std::string path = request.substr(request.find(" ") + 1);
        path = path.substr(0, path.find(" "));

        if (path == "/") {
            response = "HTTP/1.1 200 OK\r\n\r\n";
        } 
        else if (path.find("/user-agent") == 0) {
            std::string user_agent = request.substr(request.find("\r\n") + 2);
            user_agent = user_agent.substr(user_agent.find("\r\n") + 2);
            user_agent = user_agent.substr(user_agent.find("\r\n") + 2);
            user_agent = user_agent.substr(user_agent.find(" ") + 1, user_agent.find("\r") - user_agent.find(" ") - 1);
            response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: " + std::to_string(user_agent.size()) + "\r\n\r\n" + user_agent;
        } 
        else if (path.find("/echo/") == 0) {
            std::string content = path.substr(6);
            response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: " + std::to_string(content.size()) + "\r\n\r\n" + content;
        } 
        else if (path.find("/files/") == 0) {
            std::string filename = path.substr(7); // Remove "/files/"
            std::string fileContent = readFileContents(filename);
            if (!fileContent.empty()) {
                response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(fileContent.size()) + "\r\n\r\n" + fileContent;
            } else {
             response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n";
            response += "<html><body><h1>404 Not Found</h1></body></html>";
            }
        } 
        else {
             response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n";
            response += "<html><body><h1>404 Not Found</h1></body></html>";
        }
    }
    else if(method=="POST")
    {
        std::string path = request.substr(request.find(" ") + 1);
        path = path.substr(0, path.find(" "));
        if(path.find("/files")==0){
            std::string filename = path.substr(7); // Remove "/files/"
            std::string content = request.substr(request.find("\r\n\r\n") + 4);
             std::ofstream file(std::string(FILES_DIRECTORY) + "/" + filename, std::ios::binary);
            if (file)
            {
                file << content;
                file.close();
                response = "HTTP/1.1 201 Created\r\n\r\n";
            }
            else
            {
                response = "HTTP/1.1 500 Post Request Problem\r\n\r\n";
            }
        }
    }
     else {
                response = "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/html\r\n\r\n";
        response += "<html><body><h1>405 Method Not Allowed</h1></body></html>";
    }
    return response;
}
