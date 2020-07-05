#include "integer.hpp"

#include <functional>
#include <map>

using std::map;
using std::function;

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

        long int Integer::native_int() const {
            if( value.fits_slong_p() ) {
                return value.get_si();
            } else {
                throw runtime_error("Integer value does not fit signed long.");
            }
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
            return "Int";
        }

        bool
        Integer::has_interface( string const &name ) {
            return (name=="Thing"||name=="Number"||name==rhizome_type());
        }

        Thing *
        Integer::invoke( Thing *context, string const &method, Thing *arg ) {
            static rhizome::core::Dispatcher dispatcher( {
                {
                    "ϵℙ", [this]( Thing *arg ) {
                        assert(arg==NULL );
                        return (Thing*)new Bool(this->is_prime());
                    }
                },
                {
                    "+=", [this]( Thing *arg ) {
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        this->value += ((Integer*)arg)->value;
                        return (Thing*)this;
                    }
                },
                {
                    "-=", [this]( Thing *arg ) {
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        this->value -= ((Integer*)arg)->value;
                        return (Thing*)this;
                    }
                },
                {
                    "*=", [this]( Thing *arg ) {
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        this->value *= ((Integer*)arg)->value;
                        return (Thing*)this;
                    }
                },
                {
                    "/=", [this]( Thing *arg ) {
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        this->value /= ((Integer*)arg)->value;
                        return (Thing*)this;
                    }
                },
                {
                    "===", [this]( Thing *arg ) {
                        assert(arg!=NULL);
                        if( arg->rhizome_type()!=rhizome_type() ) {
                            return (Thing*)new Bool(false);
                        } else {
                            return (Thing*)new Bool(value == ((Integer*)arg)->value);
                        }        
                    }
                },
                {
                    "+", [this](Thing *arg) {
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        return (Thing*)new Integer( this->value + ((Integer*)arg)->value);
                    }
                },
                {
                    "%", [this](Thing *arg) {
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        return (Thing*)new Integer( this->value % ((Integer*)arg)->value);
                    }
                },
                {
                    "*", [this](Thing *arg) {
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        return (Thing*)new Integer( this->value * ((Integer*)arg)->value);
                    }
                },
                {
                    "-", [this](Thing *arg) {
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        return (Thing*)new Integer( this->value - ((Integer*)arg)->value);
                    }
                },
                {
                    "/", [this](Thing *arg) {
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        return (Thing*)new Integer( this->value / ((Integer*)arg)->value);
                    }
                }
            });
            if( dispatcher.count(method) > 0 ){
                return dispatcher.at(method)(arg);
            }
            stringstream err;
            err << "Unknown Int method: " << method << ".\n"; 
            if(context!=NULL) {
                err << "    Context: ";
                context->serialize_to(err);
            }
            throw runtime_error(err.str());
        }
    }
}
