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
        Bool::invoke( string const &method, Thing *argument ) {
            if( method=="!" && argument==NULL ) return new Bool( !value );
            if( method=="==" && argument!=NULL ) {
                if( argument->rhizome_type() == rhizome_type() ) {
                    Bool *b = (Bool*)argument;
                    return new Bool(b->value==value);
                }
            }
            throw runtime_error("");
        }
    }
}