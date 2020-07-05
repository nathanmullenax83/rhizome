#include "uuid.hpp"
#include "types/string.hpp"
#include <cassert>
using rhizome::core::Dispatcher;
using rhizome::types::String;

namespace rhizome {
    namespace types {
        UUID::UUID() {
            stringstream s;
            for(size_t i=0; i<RHIZOME_UUID_LENGTH; ++i) {
                s << (char) (dist(r));
            }
            value = s.str();
        }

        bool
        UUID::operator== ( UUID const &b ) const {
            return value==b.value;
        }

        

        void
        UUID::serialize_to(ostream &out) const {
            out << rhizome_type() << "(" << value;
            out << ")";
        }

        string
        UUID::rhizome_type() const {
            return "UUID";
        }

        bool
        UUID::has_interface(string const &w) {
            return (w==rhizome_type()||w=="Thing");
        }

        string
        UUID::Value() const {
            return value;
        }

        Thing *
        UUID::invoke( Thing *context, string const &method, Thing *arg ) {
            static Dispatcher dispatcher({
                {
                    "String",[] ( Thing *that, Thing * arg ) {
                        assert( arg==NULL );
                        String *s = new String(((UUID*)that)->Value());
                        return s;
                    }
                }
            });         
            try {
                Thing *r = dispatcher.at(method)(this, arg);
                return r;
            } catch( std::exception *e ) {
                stringstream err;
                err << "Error invoking " << method << " on " << rhizome_type() << ".\n";
                if( context != NULL ) {
                    err << "\nContext: \n    ";
                    context->serialize_to(err);
                }
                throw runtime_error(err.str());
            }
        }
    }
}