#include "float.hpp"

#include "types/bool.hpp"
#include <cassert>

namespace rhizome {
    namespace types {
        namespace floats {
            static Dispatcher<Float> dispatcher({
                {
                    "===",[]( Thing * context, Float *that, Thing * arg ) {
                        (void)context;
                        assert(arg!=NULL && arg->rhizome_type()==that->rhizome_type());
                        Float *f = (Float*)arg;
                        return (Thing*)new Bool(f->value==that->value);
                    }
                },
                {
                    "+=",[]( Thing * context, Float *that, Thing * arg ) {
                        (void)context;
                        assert(arg!=NULL && arg->rhizome_type()==that->rhizome_type());
                        Float *f = (Float*)arg;
                        that->value += f->value;
                        return that;
                    }
                },
                {
                    "-=",[]( Thing * context, Float *that, Thing * arg ) {
                        (void)context;
                        assert(arg!=NULL && arg->rhizome_type()==that->rhizome_type());
                        Float *f = (Float*)arg;
                        that->value -= f->value;
                        return that;
                    }
                },
                {
                    "*=",[]( Thing * context, Float *that, Thing * arg ) {
                        (void)context;
                        assert(arg!=NULL && arg->rhizome_type()==that->rhizome_type());
                        Float *f = (Float*)arg;
                        that->value *= f->value;
                        return that;
                    }
                },
                {
                    "/=",[]( Thing * context, Float *that, Thing * arg ){
                        (void)context;
                        assert(arg!=NULL && arg->rhizome_type()==that->rhizome_type());
                        Float *f = (Float*)arg;
                        that->value /= f->value;
                        return that;
                    }
                },
                {
                    "evaluate",[] ( Thing *context, Float *that, Thing *arg) {
                        assert(arg==NULL);
                        return that->evaluate(context);
                    }
                }
            });
        }

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
        Float::serialize_to( size_t level, ostream &out ) const {
            (void)level;
            out << value;
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
            return (w==rhizome_type()||w=="number"||w=="Thing");
        }

        Thing *
        Float::invoke( Thing *context, string const &method, Thing *arg ) {

            try {
                Thing *r = floats::dispatcher.at(method)(context,this,arg);
                return r;
            } catch( std::exception *e ) {
                if( floats::dispatcher.count(method)==0) {
                    throw runtime_error(rhizome::core::invoke_method_not_found(method,this,context));
                } else {
                    throw runtime_error(rhizome::core::invoke_error(method,arg,this,context,e));
                }
            }
        }

        long double
        Float::get_value() const {
            return value;
        }

        Thing *
        Float::evaluate( Thing *context ) const {
            (void)context;
            return clone();
        }
    }
}