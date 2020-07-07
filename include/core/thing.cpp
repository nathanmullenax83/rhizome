#include "thing.hpp"

namespace rhizome {
    namespace core {
        // Formatted error messages:
        string invoke_method_not_found( string const &method_name, Thing *on_object, Thing *context ) {
            stringstream err;
            err << "Method " << method_name << " does not exists on ";
            if( on_object!=NULL ) {
                on_object->serialize_to(err);
            } else {
                err << "'unspecified object.'";
            }
            if( context!=NULL ) {
                err << "    Context: ";
                context->serialize_to(err);
            }
            return err.str();
        }

        string invoke_error( string const &method_name, Thing *arg, Thing *on_object, Thing *context, std::exception *e) {
            stringstream err;
            err << "Method " << method_name << " could not be invoked on ";
            if( on_object!=NULL ) {
                on_object->serialize_to(err);
            } else {
                err << "'unspecified object.'";
            }
            if( arg!=NULL ) {
                err << "    Argument: ";
                arg->serialize_to(err);
                err << "\n";
            }
            err << "\n    Error" << e->what() << "\n";
            if( context!=NULL ) {
                err << "    Context: ";
                context->serialize_to(err);
            }
            return err.str();
        }
    }
}