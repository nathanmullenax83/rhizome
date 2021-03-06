#include "html.hpp"
#include "log.hpp"

namespace rhizome {
    namespace html {
        HTML::HTML() {

        }

        HTML::HTML( string const &title ) {
            head.title(title);
        }

        HTML::~HTML() {

        }

        void
        HTML::write_to( ostream &out, size_t indent ) const {
            (void)indent;
            out << "<!DOCTYPE html>\n";
            out << "<html>\n";
            head.write_to(out,1);
            body.write_to(out,1);
            out << "</html>\n";
        }

        void
        HTML::serialize_to( size_t level, ostream &out ) const {
            write_to(out,level);
        }

        Thing * 
        HTML::clone() const {
            HTML *doc = new HTML();
            doc->head = *((Head*)head.clone());
            doc->body = *((Body*)body.clone());
            return doc;
        }

        string
        HTML::rhizome_type() const {
            return "html::Document";
        }

        bool
        HTML::has_interface( string const &name ) {
            return (name==rhizome_type()||name=="Thing");
        }

        Thing *
        HTML::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method; (void)arg; (void)context;
            throw runtime_error("Don't know that method.");
        }
    }
}