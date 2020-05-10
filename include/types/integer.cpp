#include "integer.hpp"

namespace rhizome {
    namespace types {
        Integer::Integer(): value(0) {

        }

        Integer::Integer( int value ): value(value) {

        }

        Integer::Integer( string const &v ): value(v) {
            
        }

        Integer::Integer( mpz_class value ): value(value) {

        }

        bool
        Integer::is_prime() {
            if( value < 4e9 ) {
                return mpz_millerrabin(value.get_mpz_t(),7);
            } else {
                throw runtime_error("I don't know if that is prime...");
            }
        }

        ostream & operator << ( ostream &out, Integer const &j ) {
            out << j.value.get_str();
            return out;
        }

        bool operator< ( Integer const &a, Integer const &b ) {
            return a.value < b.value;
        }

        bool operator> (Integer const &a, Integer const &b ) {
            return a.value > b.value;
        }

        Integer operator- (Integer const &a, Integer const &b ) {
            return Integer(a.value - b.value);
        }

        Integer operator+ (Integer const &a, Integer const &b) {
            return Integer( a.value + b.value );
        }

        Integer operator/ (Integer const &a, Integer const &b ) {
            return Integer(a.value/b.value);
        }

        Integer operator* (Integer const &a, Integer const &b ) {
            return Integer(a.value*b.value);
        }

        bool operator== (Integer const &a, Integer const &b) {
            return a.value == b.value;
        }


        bool operator!= (Integer const &a, Integer const &b ) {
            return a.value != b.value;
        }
/*
        rp::Pattern *
        Integer::make_pattern() const {
            rp::Literal *zero = new rp::Literal("0");
            rp::Range *one_to_nine = new rp::Range('1','9');
            rp::Range *zero_to_nine = new rp::Range('0','9');
            rp::Star *rest = new rp::Star(zero_to_nine);
            rp::Cat *nonzero = new rp::Cat(one_to_nine,rest);
            rp::Or *branches = new rp::Or(zero,nonzero);
            rp::Group *capture = new rp::Group(branches);
            return capture;
        }

        rp::Pattern *
        Integer::make_concise_pattern() const {
            return make_pattern();
        }*/

        void
        Integer::serialize_to( ostream & out ) const {
            out << value.get_str();
        }

        Thing *
        Integer::clone() const {
            return new Integer(value);
        }

        string
        Integer::rhizome_type() const {
            return "Integer";
        }

        bool
        Integer::has_interface( string const &name ) {
            return (name=="Thing"||name=="Number"||name==rhizome_type());
        }

        Thing *
        Integer::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}
