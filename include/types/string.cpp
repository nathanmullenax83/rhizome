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

        void
        String::serialize_to( ostream &out ) const {
            out << value;
        }

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
        String::invoke( Thing *context, string const &method, Thing *arg ) {
            if( arg==NULL ) {
                if( method=="clone") {
                    return clone();
                } else if( method=="append") {
                    stringstream ss; arg->serialize_to(ss);
                    append(ss.str());
                    return this;
                }
            }
            (void)method; (void)context;
            throw runtime_error("Nothing to invoke.");
        }

        string
        String::native_string() const {
            return value;
        }
    }
}