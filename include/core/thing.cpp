#include "thing.hpp"

namespace rhizome {
    namespace core {
        // Formatted error messages:
        string invoke_method_not_found( string const &method_name, Thing *on_object, Thing *context ) {
            stringstream err;
            err << "Method " << method_name << " does not exists on ";
            if( on_object!=NULL ) {
                on_object->serialize_to(1,err);
            } else {
                err << "'unspecified object.'";
            }
            if( context!=NULL ) {
                err << "    Context: ";
                context->serialize_to(2,err);
            }
            return err.str();
        }

        string invoke_error( string const &method_name, Thing *arg, Thing *on_object, Thing *context, std::exception *e) {
            stringstream err;
            err << "Method " << method_name << " could not be invoked on ";
            if( on_object!=NULL ) {
                on_object->serialize_to(1,err);
            } else {
                err << "'unspecified object.'";
            }
            if( arg!=NULL ) {
                err << "    Argument: ";
                arg->serialize_to(2,err);
                err << "\n";
            }
            err << "\n    Error" << e->what() << "\n";
            if( context!=NULL ) {
                err << "    Context: ";
                context->serialize_to(2,err);
            }
            return err.str();
        }

        FreeList::FreeList() {

        }

        FreeList::~FreeList() {
            for( auto i=elems.begin(); i!=elems.end(); i++) {
                delete *i;
            }
        }

        Thing *
        FreeList::empty( Thing * return_value ) {
            if( elems.count(return_value) ) {
                elems.erase(return_value);
            }
            for( auto i=elems.begin(); i!=elems.end(); i++) {
                delete *i;
            }
            return return_value;
        }

        FreeList &
        FreeList::operator+=(Thing *t) {
            elems.insert(t);
            return *this;
        }

        Thing *
        FreeList::operator()(Thing *t) {
            elems.insert(t);
            return t;
        }

        string indent(size_t level) {
            return string(level*4,' ');
        }
    }
}