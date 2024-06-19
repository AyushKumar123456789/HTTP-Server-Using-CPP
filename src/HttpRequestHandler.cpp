#include "HttpRequestHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include<zlib.h>

#define FILES_DIRECTORY "../files"

// Function to read the contents of a file and return it as a string
std::string readFileContents(const std::string& filename) {
      // Create an input file stream to read the file in binary mode
    std::ifstream file_I_stores(FILES_DIRECTORY + std::string("/") + filename, std::ios::binary);
     // Check if the file was successfully opened
    if (file_I_stores) {
        // Create an output string stream to store the file's contents , it is simple as creating variable of type ostringstream name contentStream
        std::ostringstream contentStream;
         //contentStream << file_I_stores.rdbuf(); (rdbuf means read buffer) Read the entire file contents into the string stream varibale contentStream
        contentStream << file_I_stores.rdbuf();
         // Converts the stream's contents to a string and returns
        return contentStream.str();
    } else {
           // Return an empty string if the file could not be opened
        return "Error In Opening";
    }
}

std::string extractMethod(const std::string& request) {
    // Gets substring from
    return request.substr(0, request.find(" "));
}

std::string extractPath(const std::string& request) {
    // Request Format :GET /index.html HTTP/1.1
    std::string path = request.substr(request.find(" ") + 1);
    return path.substr(0, path.find(" "));
}

std::string extractAcceptEncoding(const std::string& request) {
    size_t pos = request.find("Accept-Encoding: ");
    if (pos == std::string::npos) return "";

    size_t endPos = request.find("\r\n", pos);
    return request.substr(pos + 17, endPos - pos - 17);
}

// Function to compress a string using gzip
std::string gzipCompress(const std::string& data) {
    std::string compressedData;
    z_stream zs;
    memset(&zs, 0, sizeof(zs));

    if (deflateInit2(&zs, Z_BEST_COMPRESSION, Z_DEFLATED, 15 | 16, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
        throw std::runtime_error("deflateInit2 failed");
    }

    zs.next_in = const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(data.data()));

    zs.avail_in = data.size();

    int ret;
    char outbuffer[32768];

    do {
        zs.next_out = reinterpret_cast<unsigned char*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = deflate(&zs, Z_FINISH);

        if (compressedData.size() < zs.total_out) {
            compressedData.append(outbuffer, zs.total_out - compressedData.size());
        }
    } while (ret == Z_OK);

    deflateEnd(&zs);

    if (ret != Z_STREAM_END) {
        throw std::runtime_error("deflate failed");
    }

    return compressedData;
}


std::string getResponse(const std::string& status, const std::string& contentType, const std::string& content, bool gzip = false) {
    std::string response = "HTTP/1.1 " + status + "\r\n";
    response += "Content-Type: " + contentType + "\r\n";

    std::string body = content;
    if (gzip) {
        body = gzipCompress(content);
        response += "Content-Encoding: gzip\r\n";
    }

    response += "Content-Length: " + std::to_string(body.size()) + "\r\n\r\n";
    response += body;
    return response;
}

std::string getErrorResponse(const std::string& status, const std::string& message) {
    return getResponse(status, "text/html", "<html><body><h1>" + message + "</h1></body></html>");
}

std::string getFileResponse(const std::string& path, bool gzip) {
    std::string filename = path.substr(7); // Remove "/files/"
    std::string fileContent = readFileContents(filename);
    if (!fileContent.empty()) {
        return getResponse("200 OK", "text/html", fileContent, gzip);
    } else {
        return getErrorResponse("404 Not Found", "File Might Be Empty");
    }
}

std::string getUserAgentResponse(const std::string& request, bool gzip) {
    std::string userAgent = request.substr(request.find("\r\n\r\n") + 4);
    userAgent = userAgent.substr(userAgent.find("\r\n") + 2);
    userAgent = userAgent.substr(userAgent.find("\r\n") + 2);
    userAgent = userAgent.substr(userAgent.find(" ") + 1, userAgent.find("\r") - userAgent.find(" ") - 1);
    return getResponse("200 OK", "text/plain", userAgent,gzip);
}

std::string getEchoResponse(const std::string& path, bool gzip) {
    std::string content = path.substr(6); // Remove "/echo/"
    return getResponse("200 OK", "text/plain", content,gzip);
}

std::string handleGetRequest(const std::string& path, const std::string& request) {
    std::string acceptEncoding = extractAcceptEncoding(request);
    bool gzip = acceptEncoding.find("gzip") != std::string::npos;
    
    if (path == "/") {
        return getResponse("200 OK", "text/html", "",gzip);
    } else if (path.find("/user-agent") == 0) {
        return getUserAgentResponse(request,gzip);
    } else if (path.find("/echo/") == 0) {
        return getEchoResponse(path,gzip);
    } else if (path.find("/files/") == 0) {
        return getFileResponse(path,gzip);
    } else {
        return getErrorResponse("404 Not Found", "404 Not Found");
    }
}

std::string handlePostRequest(const std::string& path, const std::string& request) {
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
    return getErrorResponse("404 Not Found", "404 Not Found");
}

std::string HttpRequestHandler::handleRequest(const std::string& request) {
    // std::cerr << "Request Line: " << request << std::endl;

    std::string method = extractMethod(request);
    std::string path = extractPath(request);

    if (method == "GET") {
        return handleGetRequest(path, request);
    } else if (method == "POST") {
        return handlePostRequest(path, request);
    } else {
        return getErrorResponse("405 Method Not Allowed", "405 Method Not Allowed");
    }
}
