#include "http_request.hpp"

namespace rhizome {
    namespace net {
        HTTPRequest::HTTPRequest(HTTPRequestMethod method, HTTPRequestVersion version) 
        : method(method), version(version) {

        }

        

        // rp::Pattern *
        // HTTPRequest::make_pattern() const {
        //     return NULL;
        // }

        // rp::Pattern *
        // HTTPRequest::make_concise_pattern() const {
        //     return NULL;
        // }

        // rp::Pattern *
        // HTTPRequest::pattern_request_method() {
        //     rp::Or *options = new rp::Or();
        //     options->add_clause( new rp::Literal("CONNECT") );
        //     options->add_clause( new rp::Literal("DELETE") );
        //     options->add_clause( new rp::Literal("GET") );
        //     options->add_clause( new rp::Literal("HEAD"));
        //     options->add_clause( new rp::Literal("PUT") );
        //     options->add_clause( new rp::Literal("DELETE"));
        //     options->add_clause( new rp::Literal("OPTIONS"));
        //     options->add_clause( new rp::Literal("TRACE"));
        //     return options;
        // }

        // rp::Pattern *
        // HTTPRequest::pattern_request_uri() {
        //     rp::Or *options = new rp::Or();
        //     // '*' is an option
        //     options->add_clause( new rp::Literal("*") );
        //     // todo
        //     // absolute URI
        //     // absolute path
        //     // authority
        //     return options;
        // }

        // rp::Pattern *
        // HTTPRequest::pattern_request_proto() {
        //     rp::Or *p = new rp::Or();
        //     p->add_clause( new rp::Literal("HTTP/1.1") );
        //     return p;

        // }

        // rp::Pattern *
        // HTTPRequest::pattern_request_line() {
        //     rp::Cat *line = new rp::Cat();
        //     line->append( pattern_request_method() );
        //     line->append( pattern_request_uri() );
        //     line->append( pattern_request_proto() );
        //     return line;
        // }
    }
}