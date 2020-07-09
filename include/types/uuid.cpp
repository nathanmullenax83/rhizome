#include "uuid.hpp"
#include "types/string.hpp"
#include <cassert>
using rhizome::core::Dispatcher;
using rhizome::core::indent;
using rhizome::types::String;

namespace rhizome {
    namespace types {
        namespace uuid {
            static Dispatcher<UUID> dispatcher({
                {
                    "String",[] ( Thing *context, UUID *that, Thing * arg ) {
                        (void)context;
                        assert( arg==NULL );
                        String *s = new String(that->Value());
                        return s;
                    }
                }
            }); 
        }

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
        UUID::serialize_to(size_t level, ostream &out) const {
            out << indent(level) << rhizome_type() << "(" << value;
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
        
            try {
                Thing *r = uuid::dispatcher.at(method)(context,this, arg);
                return r;
            } catch( std::exception *e ) {
                stringstream err;
                err << "Error invoking " << method << " on " << rhizome_type() << ".\n";
                if( context != NULL ) {
                    err << "\nContext: \n    ";
                    context->serialize_to(1,err);
                }
                throw runtime_error(err.str());
            }
        }

        Thing *
        UUID::evaluate( Thing *context ) const {
            (void)context;
            return clone();
        }
    }
}