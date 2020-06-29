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
        HTML::write_to( ostream &out ) {

            out << "<!DOCTYPE html>\n";
            out << "<html>\n";
            head.write_to(out);
            body.write_to(out);
            out << "</html>\n";
        }

        void
        HTML::serialize_to( ostream &out ) const {
            out << "html(";
            head.serialize_to(out);
            body.serialize_to(out);
            out << ")";
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
        HTML::invoke( string const &method, Thing *arg ) {
            (void)method; (void)arg;
            throw runtime_error("Don't know that method.");
        }
    }
}