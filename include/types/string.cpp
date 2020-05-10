#include "string.hpp"

namespace rhizome {
    namespace types {
        String::String(): value("") {

        }

        String::String(string const&v): value(v) {

        }

        ostream & operator << ( ostream & out, String const &s ) {
            out << s.value;
            return out;
        }

        // rp::Pattern *
        // String::make_pattern() const {
        //     return make_concise_pattern();
        // }

        // rp::Pattern *
        // String::make_concise_pattern() const {
        //     rp::Cat *p = new rp::Cat();
        //     p->append( new rp::Literal("\"") );
            
        //     p->append( new rp::Literal("\"") );
        //     return p;
        // }

        void
        String::serialize_to( ostream &out ) const {
            out << value;
        }

        // void
        // String::deserialize_from( istream &in, IParser *parser ) {
        //     parser->match_literal( in, "string");
        //     parser->match_literal( in, "(");
        //     value = parser->match_qstring(in);
        //     parser->match_literal( in, ")");
        // }

        Thing *
        String::clone() const {
            return new String(value);
        }

        string
        String::rhizome_type() const {
            return "String";
        }

        void 
        String::append( string const &w ) {
            stringstream ss;
            ss << value << w;
            value = ss.str();
        }

        bool
        String::has_interface(string const &w) {
            return (w==rhizome_type()||w=="Thing");
        }

        Thing *
        String::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}