#include "fraction.hpp"


namespace rhizome {
    namespace types {
        Fraction::Fraction(Integer numerator, Integer denomenator ) {
            if( numerator < 0 && denomenator < 0 ) {
                Integer d = gcd(0-numerator,0-denomenator);
                this->numerator = (0-numerator)/d;
                this->denomenator = (0-denomenator)/d;
            } else if( numerator > 0 && denomenator < 0 ) {
                Integer d = gcd(numerator,0-denomenator);
                this->numerator = (0-numerator)/d;
                this->denomenator = (0-denomenator)/d;
            } else {
                Integer d = gcd(numerator,denomenator);
                this->numerator = numerator/d;
                this->denomenator = denomenator/d;
            }
        }

        Integer
        Fraction::gcd( Integer a, Integer b ) {
            a = a < 0 ? 0-a : a;
            b = b < 0 ? 0-b : b;
            /// Until a or b is 0 or,
            /// subtract the smaller number from the larger number.
            /// . The number that is not zero is the GCD.
            while( a != 0 && b != 0) {
                if( a > b ) {
                    a = a - b;
                } else {
                    b = b - a;
                }
            }
            return std::max(a,b);
        }

        void
        Fraction::serialize_to( ostream &out ) const {
            out << rhizome_type() << "(";
            out << numerator << "/" << denomenator;
            out << ")";
        }

        std::ostream &
        operator<< ( std::ostream &out, Fraction const &q ) {
            out << q.numerator << "/" << q.denomenator;
            return out;
        }

        Fraction
        Fraction::operator+ (Fraction const &f2) const {
            return Fraction( numerator+f2.numerator, denomenator+f2.denomenator );
        }

        Thing *
        Fraction::clone() const {
            Fraction *f = new Fraction(numerator,denomenator);
            return f;
        }

        string Fraction::rhizome_type() const {
            return "Rational";
        }

        bool
        Fraction::has_interface( string const &w ) {
            return w=="Thing"||w=="Number"||w==rhizome_type();
        }

        Thing *
        Fraction::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }

        long double
        Fraction::decimal() const {
            long double n = numerator.native_int();
            long double d = denomenator.native_int();
            return n/d;// customize
        }
    }
}