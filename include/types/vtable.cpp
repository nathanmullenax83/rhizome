#include "vtable.hpp"

namespace rhizome {
    namespace types {
        VTable::VTable() {

        }

        string record_not_found( string const &expected_sig, string const &name ) {
            stringstream s;
            s << "Could not find a record with " << expected_sig << " and name " << name;
            return s.str();
        }

        Thing * 
        VTable::lookup( string const &signature, string const &name ) {
            if( vtable.count(signature) < 0 ) {
                if( vtable[signature].count(name) > 0 ) {
                    return vtable[signature][name];
                } 
            } 
            throw runtime_error(record_not_found(signature,name));
        }

        Tuple *
        VTable::lookup( string const &signature ) {
            Tuple *r = new Tuple();
            if( vtable.count(signature)> 0) {
                auto &subtable  = vtable[signature];
                for( auto elem=subtable.begin(); elem!=subtable.end(); elem++) {
                    r->append(elem->second);
                }
            }
            return r;
        }

        void
        VTable::insert( string const &name, Thing *t) {
            vtable[t->rhizome_type()].insert(name,t);
        }

        string
        VTable::rhizome_type() const {
            return "VTable";
        }

        void
        VTable::serialize_to( std::ostream &out ) const {
            out << rhizome_type() << "{";
            for( auto type_sets = vtable.begin(); type_sets != vtable.end(); type_sets++) {
                // signature
                out << type_sets->first;
                out << ": {";
                for( auto elem = type_sets->second.begin(); elem!=type_sets->second.end(); elem++) {
                    out << elem->first << ":";
                    elem->second->serialize_to(out);
                }
                out << "}";
            }
            out << "}";
        }

        bool 
        VTable::has_interface( string const &name) {
            return name=="Thing"||name==rhizome_type();
        }

        Thing *
        VTable::invoke( string const &name, Thing *arg ) {
            // invoking a function named /thing/ on arg
            if( arg != NULL ) {
                string arg_type = arg->rhizome_type();
                // look for something that takes that type of argument.
                
            } else {
                // recieved null ( same as () )as an argument, so we're looking for something
                // that take () and returns... whatever the context calls for. Since we don't
                // have context in this version of invoke, we can still evaluate!

                // For argument's sake:
                // If there are multiple ()->'a functions, then all of the possible evaluations
                // are returned as a tuple.
            }
        }

        Thing *
        VTable::invoke( string const &name ) {
            return invoke( name, NULL );
        }


        Thing *
        VTable::invoke_x( string const &name, Thing *arg, TypeConstraint *arg_constraint ) {

            // Use the other version if the type is unconstrained.
            assert(arg_constraint!=NULL);

            if( arg_constraint->contains(arg)) {
                
            } else {
                stringstream err;
                err << "Parameter ";
                arg->serialize_to(err);
                err << " does not satisfy constraint ";
                arg_constraint->serialize_to(err);
                err << ".";
                throw runtime_error(err.str());
            }
        }

    }
}