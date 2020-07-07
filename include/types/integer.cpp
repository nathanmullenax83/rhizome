#include "integer.hpp"

#include <functional>
#include <map>

using std::map;
using std::function;
using rhizome::core::Dispatcher;

namespace rhizome {
    namespace types {
        namespace integer {
            static Dispatcher<Integer> dispatcher( {
                {
                    "ϵℙ", []( Thing *context, Integer *that, Thing *arg ) {
                        (void)context;
                        assert(arg==NULL );
                        assert( that->rhizome_type()=="Int");
                        return (Thing*)new Bool(((Integer*)that)->is_prime());
                    }
                },
                {
                    "+=", []( Thing *context, Integer *that, Thing *arg ) {
                        (void)context;
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        ((Integer*)that)->value += ((Integer*)arg)->value;
                        return that;
                    }
                },
                {
                    "-=", []( Thing *context, Integer *that, Thing *arg ) {
                        (void)context;
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        ((Integer*)that)->value -= ((Integer*)arg)->value;
                        return that;
                    }
                },
                {
                    "*=", []( Thing *context, Integer *that, Thing *arg ) {
                        (void)context;
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        ((Integer*)that)->value *= ((Integer*)arg)->value;
                        return that;
                    }
                },
                {
                    "/=", []( Thing *context, Integer *that, Thing *arg ) {
                        (void)context;
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        ((Integer*)that)->value /= ((Integer*)arg)->value;
                        return that;
                    }
                },
                {
                    "===", []( Thing *context, Integer *that, Thing *arg ) {
                        (void)context;
                        assert(arg!=NULL);
                        if( arg->rhizome_type()!=that->rhizome_type() ) {
                            return (Thing*)new Bool(false);
                        } else {
                            Integer *t = (Integer*)that;
                            return (Thing*)new Bool(t->value == ((Integer*)arg)->value);
                        }        
                    }
                },
                {
                    "+", []( Thing *context, Integer *that, Thing *arg ) {
                        (void)context;
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        return (Thing*)new Integer( ((Integer*)that)->value + ((Integer*)arg)->value);
                    }
                },
                {
                    "%", []( Thing *context, Integer *that, Thing *arg ) {
                        (void)context;
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        return (Thing*)new Integer( ((Integer*)that)->value % ((Integer*)arg)->value);
                    }
                },
                {
                    "*", []( Thing *context, Integer *that, Thing *arg ) {
                        (void)context;
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        return (Thing*)new Integer( ((Integer*)that)->value * ((Integer*)arg)->value);
                    }
                },
                {
                    "-", []( Thing *context, Integer *that, Thing *arg ) {
                        (void)context;
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        return (Thing*)new Integer( ((Integer*)that)->value - ((Integer*)arg)->value);
                    }
                },
                {
                    "/", []( Thing *context, Integer *that, Thing *arg ) {
                        (void)context;
                        assert(arg!=NULL);
                        assert(arg->rhizome_type()=="Int");
                        return (Thing*)new Integer( ((Integer*)that)->value / ((Integer*)arg)->value);
                    }
                },
                {
                    "evaluate", [] (Thing *context, Integer *that, Thing *arg) {
                        assert(arg==NULL);
                        return that->evaluate(context);
                    }
                }
            });
        }

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
            try {
                Thing *r =  integer::dispatcher.at(method)(context,this,arg);
                return r;
            } catch( std::exception *e ) {
                if( integer::dispatcher.count(method)==0) {
                    throw runtime_error(rhizome::core::invoke_method_not_found(method,this,context));
                } else {
                    throw runtime_error(rhizome::core::invoke_error(method,arg,this,context,e));
                }
            }
        }

        Thing *
        Integer::evaluate( Thing *context ) const {
            (void)context;
            return clone();
        }
    }
}
