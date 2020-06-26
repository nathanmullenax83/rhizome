#ifndef RHIZOME_NET_SOCKET_SERVER_HPP
#define RHIZOME_NET_SOCKET_SERVER_HPP

#include <iostream>
#include <sstream>
#include <functional>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include "log.hpp"
#include "core/thing.hpp"

using rhizome::core::Thing;
using std::string;
using std::thread;
using std::stringstream;

namespace rl = rhizome::log;


namespace rhizome {
    namespace net {
        class SocketServer: public Thing {
        protected:
            int port_no;
            int socket_fd;
            rl::Log server_log;
            bool serving;
            struct sockaddr_in address;

        public:
            SocketServer( int port_no, size_t queue_length=100 );            
        };
    }
}

#endif
