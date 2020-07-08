#include "fraction.hpp"
#include <cassert>

using rhizome::core::Dispatcher;

namespace rhizome {
    namespace types {

        namespace fractions {
            static Dispatcher<Fraction> dispatcher({
                {
                    "evaluate", [](Thing *context, Fraction *that, Thing *arg ) {
                        assert(arg==NULL);
                        return that->evaluate(context);
                    }
                }
            });
        }

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
            return "Frac";
        }

        bool
        Fraction::has_interface( string const &w ) {
            return w=="Thing"||w=="Number"||w==rhizome_type();
        }

        Thing *
        Fraction::invoke( Thing *context, string const &method, Thing *arg ) {
            try {
                Thing *r =  fractions::dispatcher.at(method)(context,this,arg);
                return r;
            } catch( std::exception *e ) {
                if( fractions::dispatcher.count(method)==0) {
                    throw runtime_error(rhizome::core::invoke_method_not_found(method,this,context));
                } else {
                    throw runtime_error(rhizome::core::invoke_error(method,arg,this,context,e));
                }
            }
        }

        long double
        Fraction::decimal() const {
            long double n = numerator.native_int();
            long double d = denomenator.native_int();
            return n/d;// customize
        }

        Thing *
        Fraction::evaluate( Thing *context) const {
            (void)context;
            return clone();
        }
    }
}