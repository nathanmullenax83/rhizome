#ifndef RHIZOME_NET_HTTP_RESPONSE_HPP
#define RHIZOME_NET_HTTP_RESPONSE_HPP

#include "types.hpp"

using rhizome::core::Thing;

namespace rhizome {
    namespace net {
        class HTTPResponse: public Thing {
        public:
            HTTPResponse();

            // virtual rp::Pattern * make_pattern();
            // virtual rp::Pattern * make_concise_pattern();
        };
    }
}

#endif
