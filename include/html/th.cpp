#include "th.hpp"

namespace rhizome {
    namespace html {
        Th::Th(string const &text, string const &scope): cdata(text) {
            (*this)["scope"] = scope;
        }

        Th::~Th() {

        }

        void Th::write_to( ostream &out, size_t indent ) {
            string spacer(indent*4,' ');
            out << spacer << "<th>" << cdata <<  "</th>\n";
        }

        void Th::serialize_to( ostream &out ) const {
            out << "th(";
            serialize_children(out);
            out << ")";
        }

        // void Th::deserialize_from( istream &in, IParser *parser ) {
            
        // }

        Thing *
        Th::clone() const {
            Th *h = new Th( attributes.at("scope"));
            h->children = clone_children();
            return h;
        }

        string
        Th::rhizome_type() const {
            return "html::Th";
        }

        Thing *
        Th::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method; (void)arg;
            throw runtime_error("No such method.");
        }

    }
}