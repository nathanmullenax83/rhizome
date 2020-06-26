#include "http_request.hpp"

namespace rhizome {
    namespace net {
        HTTPRequest::HTTPRequest(HTTPRequestMethod method, HTTPRequestVersion version) 
        : method(method), version(version) {

        }
    }
}