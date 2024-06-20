#include "HttpRequestHandler.h"
#include "ResponseUtil.h"
#include "RequestUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include<zlib.h>



std::string HttpRequestHandler::handleRequest(const std::string& request) {
    // std::cerr << "Request Line: " << request << std::endl;

    std::string method = RequestUtil::extractMethod(request);
    std::string path = RequestUtil::extractPath(request);

    if (method == "GET") {
        return RequestUtil::handleGetRequest(path, request);
    } else if (method == "POST") {
        return RequestUtil::handlePostRequest(path, request);
    } else {
        return ResponseUtil::getErrorResponse("405 Method Not Allowed", "405 Method Not Allowed");
    }
}
