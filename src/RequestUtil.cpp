#include "ResponseUtil.h"
#include "RequestUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include<zlib.h>
#define FILES_DIRECTORY "../files"

std::string RequestUtil::extractMethod(const std::string& request) {
    // Gets substring from
    return request.substr(0, request.find(" "));
}

std::string RequestUtil::extractPath(const std::string& request) {
    // Request Format :GET /index.html HTTP/1.1
    std::string path = request.substr(request.find(" ") + 1);
    return path.substr(0, path.find(" "));
}

std::string RequestUtil::extractAcceptEncoding(const std::string& request) {
    size_t pos = request.find("Accept-Encoding: ");
    if (pos == std::string::npos) return "";

    size_t endPos = request.find("\r\n", pos);
    return request.substr(pos + 17, endPos - pos - 17);
}

std::string RequestUtil::handleGetRequest(const std::string& path, const std::string& request) {
    std::string acceptEncoding = extractAcceptEncoding(request);
    bool gzip = acceptEncoding.find("gzip") != std::string::npos;
    
    if (path == "/") {
        return ResponseUtil::getResponse("200 OK", "text/html", "",gzip);
    } else if (path.find("/user-agent") == 0) {
        return ResponseUtil::getUserAgentResponse(request,gzip);
    } else if (path.find("/echo/") == 0) {
        return ResponseUtil::getEchoResponse(path,gzip);
    } else if (path.find("/files/") == 0) {
        return ResponseUtil::getFileResponse(path,gzip);
    } else {
        return ResponseUtil::getErrorResponse("404 Not Found", "404 Not Found");
    }
}

std::string RequestUtil::handlePostRequest(const std::string& path, const std::string& request) {
    if (path.find("/files") == 0) {
        std::string filename = path.substr(7); // Remove "/files/"
        std::string content = request.substr(request.find("\r\n\r\n") + 4);
        std::ofstream file(FILES_DIRECTORY + std::string("/") + filename, std::ios::binary);
        if (file) {
            file << content;
            return "HTTP/1.1 201 Created\r\n\r\n";
        } else {
            return "HTTP/1.1 500 Post Request Problem\r\n\r\n";
        }
    }
    return ResponseUtil::getErrorResponse("404 Not Found", "404 Not Found");
}
