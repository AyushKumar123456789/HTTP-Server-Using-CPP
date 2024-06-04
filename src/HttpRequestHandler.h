#ifndef HTTP_REQUEST_HANDLER_H//Header Guard
#define HTTP_REQUEST_HANDLER_H

#include <string>

class HttpRequestHandler {
public:
    static std::string handleRequest(const std::string& request);
};

#endif // HTTP_REQUEST_HANDLER_H
