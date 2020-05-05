#include "socket_server.hpp"

namespace rhizome {
    namespace net {
        SocketServer::SocketServer(int port_no, size_t queue_length): port_no(port_no), server_log("server"), serving(false) {
            if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
                server_log.error("Couldn't create socket file descriptor.");
            } else {
                server_log.info("Socket opened.");
            }
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            // htons = system byte order to network byte order...
            address.sin_port = htons(port_no);
            memset(address.sin_zero, '\0', sizeof address.sin_zero);
            if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address))<0) {
                server_log.error("Couldn't bind socket to specified port.");
            } else {
                stringstream ss;
                ss << "Socket bound to port " << port_no;
                server_log.info( ss.str() );
            }
            if (listen(socket_fd, queue_length) < 0) {
                server_log.error("Couldn't listen!");
            } else {
                stringstream ss;
                ss << "Listening on port " << port_no;
                server_log.info(ss.str());
            }
        }

        // rp::Pattern *
        // SocketServer::make_pattern() {
        //     return NULL;
        // }

        // rp::Pattern *
        // SocketServer::make_concise_pattern() {
        //     return NULL;
        // }
    }
}