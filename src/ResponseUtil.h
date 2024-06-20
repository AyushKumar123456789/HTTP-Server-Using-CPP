#ifndef RESPONSE_UTIL_H
#define RESPONSE_UTIL_H

#include <string>

class ResponseUtil {
public:
    static std::string readFileContents(const std::string& filename);
    static std::string gzipCompress(const std::string& data);
    static std::string getResponse(const std::string& status, const std::string& contentType, const std::string& content, bool gzip=false);
    static std::string getErrorResponse(const std::string& status, const std::string& message);
    static std::string getFileResponse(const std::string& path, bool gzip);
    static std::string getUserAgentResponse(const std::string& request, bool gzip);
    static std::string getEchoResponse(const std::string& path, bool gzip);
};

#endif // RESPONSE_UTIL_H
