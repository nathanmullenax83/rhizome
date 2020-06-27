#include "float.hpp"

namespace rhizome {
    namespace types {
        Float::Float(): value(0) {

        }

        Float::Float(long double value): value(value) {

        }

        Float::Float( string const &v ) {
            stringstream ss;
            ss << v;
            ss >> value;
        }

        void
        Float::serialize_to( ostream &out ) const {
            out << rhizome_type() << "(";
            out << value;
            out << ")";
        }

        Thing *
        Float::clone() const {
            return new Float(value);
        }

        
        ostream & operator << ( ostream &out, Float const &j ) {
            out << j.value;
            return out;
        }

        string
        Float::rhizome_type() const {
            return "Decimal";
        }

        bool
        Float::has_interface(string const &w) {
            return (w==rhizome_type()||w=="Number"||w=="Thing");
        }

        Thing *
        Float::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }

        long double
        Float::get_value() const {
            return value;
        }
    }
}