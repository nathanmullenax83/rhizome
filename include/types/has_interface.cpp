#include "has_interface.hpp"

namespace rhizome {
    namespace types {

        HasInterface::HasInterface( string const &name )
        : interface_name(name) {

        }

        bool
        HasInterface::contains( Thing *t ) const {
            return t->has_interface(interface_name);
        }

        // Thing impl
        string 
        HasInterface::rhizome_type() const {
            return "tc.HasInterface";
        }

        void
        HasInterface::serialize_to( size_t level, std::ostream &out ) const {
            (void)level;
            out << " has " << interface_name;
        }

        bool
        HasInterface::has_interface( string const &name ) {
            return name==rhizome_type()||name=="tc"||name=="Thing";
        }

        Thing *
        HasInterface::clone() const {
            return new HasInterface(interface_name);
        }

        string unfamiliar_method( string const &name, string const &rt, Thing *arg) {
            stringstream err;
            err << "Attempted to invoke " << name << " on " << rt << " ";
            err << "but " << rt << " is unfamiliar with that method.";
            err << " The argument was:\n";
            if( arg != NULL ){
                arg->serialize_to(1,err);
            } else {
                err << "()";
            }
            return err.str();
        }

        Thing *
        HasInterface::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)context;
            if( method=="contains" || method=="has") {
                return new rhizome::types::Bool(contains(arg));
            } 
            throw runtime_error(unfamiliar_method(method,rhizome_type(),arg));
        }
    }
}