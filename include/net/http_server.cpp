#include "http_server.hpp"



namespace rhizome {
    namespace net {

        HTTPServer::HTTPServer()
        : SocketServer(8080,10) {
            
        }

        HTTPServer::HTTPServer(int port_no, size_t queue_length)
        : SocketServer(port_no,queue_length) {

        }

        void
        HTTPServer::serialize_to( ostream &out ) const {
            out << "httpserver(";
            // out << "#portno:" << port_no; // or something like it.
            out << ")";
        }

        Thing *
        HTTPServer::clone() const {
            throw runtime_error("Two servers can't run on the same port! Are you sure you didn't want to serialize the server's configuration?");
        }

        string
        HTTPServer::rhizome_type() const {
            return "net::HTTPServer";
        }

        bool
        HTTPServer::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }

        Thing *
        HTTPServer::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)arg; (void)method; (void)context;
            throw runtime_error("Not implemented.");
        }

    }
}