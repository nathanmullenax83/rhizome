#include "char.hpp"

using rhizome::core::Dispatcher;

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
            static Dispatcher dispatcher({
                
            });
            try {
                Thing *r = dispatcher.at(method)(this,arg);
                return r;
            } catch(std::exception *e) {
                stringstream err;
                err << "Could not invoke method " << method << " on " << rhizome_type() << "\n";
                if( context != NULL ) {
                    err << "Context:\n    ";
                    context->serialize_to(err);
                }
                err << "\nError: " << e->what() << "\n";
                throw runtime_error(err.str());
            }
            
        }


    }
}