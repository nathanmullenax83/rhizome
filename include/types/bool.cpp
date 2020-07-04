#include "bool.hpp"

namespace rhizome {
    namespace types {
        Bool::Bool( bool value ): value(value) {

        }

        void
        Bool::serialize_to(std::ostream &out) const {
            out << (value?"true":"false");
        }

        string
        Bool::rhizome_type() const {
            return "Bool";
        }

        bool
        Bool::has_interface( string const &name ) {
            return name==rhizome_type() || name=="Thing";
        }

        Thing *
        Bool::clone() const {
            return new Bool(value);
        }

        Thing *
        Bool::invoke( Thing *context, string const &method, Thing *argument ) {
            (void)context;
            if( (method=="!" || method=="not" || method=="~") && argument==NULL ) return new Bool( !value );
            if( argument != NULL ) {
                if( method=="=="  ) {
                    if( argument->rhizome_type() == rhizome_type() ) {
                        Bool *b = (Bool*)argument;
                        return new Bool(b->value==value);
                    }
                }
                if( method=="=" && argument->rhizome_type()==rhizome_type()) {
                    value = ((Bool*)argument)->value;
                    return this;
                } else if( method=="&=" && argument->rhizome_type()==rhizome_type()) {
                    value = value && ((Bool*)argument)->value;
                    return this;
                } else if( method=="|=" && argument->rhizome_type()==rhizome_type()) {
                    value = value || ((Bool*)argument)->value;
                    return this;
                } else if( (method=="⊕=" || method=="⊻=") && argument->rhizome_type()==rhizome_type()) {
                    value = value ^ ((Bool*)argument)->value;
                    return this;
                }
            }
            throw runtime_error("I'm not familiar with that operation.");
        }
    }
}