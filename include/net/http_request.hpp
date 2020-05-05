#ifndef RHIZOME_NET_HTTP_REQUEST_HPP
#define RHIZOME_NET_HTTP_REQUEST_HPP

#include "core/thing.hpp"

using rhizome::core::Thing;




namespace rhizome {
    namespace net {
        enum HTTPRequestMethod {
            GET,
            PUT,
            POST,
            HEAD,
            DELETE,
            PATCH,
            OPTIONS
        };

        

        enum HTTPRequestVersion {
            HTTP_1_0,
            HTTP_1_1,
            HTTP_2_0
        };

        class HTTPRequest: public Thing {
        private:
            HTTPRequestMethod method;
            HTTPRequestVersion version;


            // Pattern * pattern_request_method();
            // Pattern * pattern_request_uri();
            // Pattern * pattern_request_line();
            // Pattern * pattern_request_proto();
        public:
            HTTPRequest(HTTPRequestMethod method, HTTPRequestVersion version);

            // virtual Pattern * make_pattern() const;
            // virtual Pattern * make_concise_pattern() const;
        };
    }
}

#endif