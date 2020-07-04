#include "type_is.hpp"

#include "types/bool.hpp"

namespace rhizome {
    namespace types {
        TypeIs::TypeIs(string const &tn) {
            type_name = tn;
        }

        bool
        TypeIs::contains(Thing *t) const {
            if( t==NULL ) return false;
            return t->rhizome_type()==type_name;
        }

        string
        TypeIs::rhizome_type() const {
            return "tc.TypeIs";
        }

        void
        TypeIs::serialize_to( std::ostream &out ) const {
            out << ":" << type_name;
        }

        Thing *
        TypeIs::clone() const {
            TypeIs *t = new TypeIs(type_name);
            return t;
        }

        bool
        TypeIs::has_interface( string const &name ) {
            return name=="Thing"||name=="tc"||name==rhizome_type();
        }

        string unfamiliar_method( string const &name, string const &rt, Thing *arg) {
            stringstream err;
            err << "Attempted to invoke " << name << " on " << rt << " ";
            err << "but " << rt << " is unfamiliar with that method.";
            err << " The argument was: ";
            if( arg != NULL ){
                arg->serialize_to(err);
            } else {
                err << "()";
            }
            return err.str();
        }

        Thing *
        TypeIs::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)context;
            if( method=="contains" || method==":") {
                rhizome::types::Bool *result = new Bool(contains(arg));
                return result;
            } else if (method=="clone") {
                return clone();
            }
            throw runtime_error(unfamiliar_method(method,rhizome_type(),arg));
            
        }
    }
}
