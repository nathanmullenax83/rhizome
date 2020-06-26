#ifndef RHIZOME_NET_HTTP_SERVER_HPP
#define RHIZOME_NET_HTTP_SERVER_HPP

#include <iostream>
#include <sstream>
#include <functional>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include "log.hpp"
#include "types.hpp"
#include "socket_server.hpp"

using rhizome::core::Thing;
using std::string;
using std::thread;
using std::stringstream;
using std::ostream;

namespace rl = rhizome::log;

namespace rhizome {
    namespace net {
        

        class HTTPServer: public SocketServer {

        public:
            HTTPServer();
            HTTPServer(int port_no, size_t queue_length);

            // virtual rp::Pattern * make_pattern() const override;
            // virtual rp::Pattern * make_concise_pattern() const override;
            
            virtual void serialize_to( ostream &out ) const override;
            // virtual void deserialize_from( istream &in, IParser *parser ) override;

            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;
        };
    }
}

#endif
