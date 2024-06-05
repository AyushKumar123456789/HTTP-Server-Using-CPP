#include "HttpRequestHandler.h"

#include <iostream>

std::string HttpRequestHandler::handleRequest(const std::string& request) {
    std::cerr << "Request Line New: " << request << std::endl;
    //request = GET /user-agent HTTP/1.1\r\n // Headers Host: localhost:4221\r\n User-Agent: foobar/1.2.3\r\n  // Read this value Accept: */*\r\n\r\n

// Request body (empty)
    std::string response;
    std::string method = request.substr(0, request.find(" "));
    if (method == "GET") {
        std::string path = request.substr(request.find(" ") + 1);
        //Here path is /some_url HTTP/1.1\r\n..............
        path = path.substr(0, path.find(" "));

        if (path == "/") {
            response = "HTTP/1.1 200 OK\r\n\r\n";
        } 
        else if(path.find("/user-agent")==0){
            std::string user_agent = request.substr(request.find("\r\n")+2);

            user_agent = user_agent.substr(user_agent.find("\r\n")+2);

            user_agent = user_agent.substr(user_agent.find("\r\n")+2);

            user_agent = user_agent.substr(user_agent.find(" ")+1,user_agent.find("\r")-user_agent.find(" ")-1);
          
            response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: " + std::to_string(user_agent.size()) + "\r\n\r\n" + user_agent;
            // for(char x: user_agent){
            //     std::cout<<x<<std::endl;
            // }
        }
        else if (path.find("/echo/") == 0) {
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
