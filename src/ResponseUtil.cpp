#include "ResponseUtil.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include<zlib.h>

#define FILES_DIRECTORY "../files"

// Function to read the contents of a file and return it as a string
std::string ResponseUtil::readFileContents(const std::string& filename) {
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

// Function to compress a string using gzip
std::string ResponseUtil::gzipCompress(const std::string& data) {
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

std::string ResponseUtil::getErrorResponse(const std::string& status, const std::string& message) {
    return ResponseUtil::getResponse(status, "text/html", "<html><body><h1>" + message + "</h1></body></html>");
}

std::string ResponseUtil::getFileResponse(const std::string& path, bool gzip) {
    std::string filename = path.substr(7); // Remove "/files/"
    std::string fileContent = readFileContents(filename);
    if (!fileContent.empty()) {
        return ResponseUtil::getResponse("200 OK", "text/html", fileContent, gzip);
    } else {
        return ResponseUtil::getErrorResponse("404 Not Found", "File Might Be Empty");
    }
}

std::string ResponseUtil::getUserAgentResponse(const std::string& request, bool gzip) {
    std::string userAgent = request.substr(request.find("\r\n\r\n") + 4);
    userAgent = userAgent.substr(userAgent.find("\r\n") + 2);
    userAgent = userAgent.substr(userAgent.find("\r\n") + 2);
    userAgent = userAgent.substr(userAgent.find(" ") + 1, userAgent.find("\r") - userAgent.find(" ") - 1);
    return ResponseUtil::getResponse("200 OK", "text/plain", userAgent,gzip);
}




std::string ResponseUtil::getEchoResponse(const std::string& path, bool gzip) {
    std::string content = path.substr(6); // Remove "/echo/"
    return ResponseUtil::getResponse("200 OK", "text/plain", content,gzip);
}



std::string ResponseUtil::getResponse(const std::string& status, const std::string& contentType, const std::string& content, bool gzip ) {
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
