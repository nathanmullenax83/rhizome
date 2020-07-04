#include "char.hpp"

namespace rhizome {
    namespace types {
        Char::Char(): v(0) {

        }

        Char::Char( wchar_t v): v(v) {

        }

        string
        Char::rhizome_type() const {
            return "Char";
        }

        bool
        Char::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }

        void
        Char::serialize_to( std::ostream &out ) const {
            out << v;
        }

        Thing *
        Char::clone() const {
            return new Char(v);
        }

        Thing *
        Char::invoke( Thing *context, string const &method, Thing *arg ) {
            // must dispatch quickly here. No if/then/else if/else if/else if...
            (void)method;(void)arg; (void)context;
            throw runtime_error("Nothing to invoke.");
        }


    }
}