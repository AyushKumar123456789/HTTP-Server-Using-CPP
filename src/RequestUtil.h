#ifndef REQUEST_UTIL_H//Header Guard
#define REQUEST_UTIL_H

#include <string>

class RequestUtil {
public:
    static std::string handleGetRequest(const std::string& path, const std::string& request);
    static std::string handlePostRequest(const std::string& path, const std::string& request);
    static std::string extractMethod(const std::string& request);
    static std::string extractPath(const std::string& request);
    static std::string extractAcceptEncoding(const std::string& request);
};

#endif // HTTP_REQUEST_HANDLER_H
