#include "float.hpp"

#include "types/bool.hpp"
#include <cassert>

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
            return (w==rhizome_type()||w=="number"||w=="Thing");
        }

        Thing *
        Float::invoke( Thing *context, string const &method, Thing *arg ) {
            static Dispatcher dispatcher({
                {
                    "===",[this]( Thing * arg ) {
                        assert(arg!=NULL && arg->rhizome_type()==rhizome_type());
                        Float *f = (Float*)arg;
                        return (Thing*)new Bool(f->value==value);
                    }
                },
                {
                    "+=",[this](Thing *arg) {
                        assert(arg!=NULL && arg->rhizome_type()==rhizome_type());
                        Float *f = (Float*)arg;
                        value += f->value;
                        return (Thing*)this;
                    }
                },
                {
                    "-=",[this](Thing *arg) {
                        assert(arg!=NULL && arg->rhizome_type()==rhizome_type());
                        Float *f = (Float*)arg;
                        value -= f->value;
                        return (Thing*)this;
                    }
                },
                {
                    "*=",[this](Thing *arg) {
                        assert(arg!=NULL && arg->rhizome_type()==rhizome_type());
                        Float *f = (Float*)arg;
                        value *= f->value;
                        return (Thing*)this;
                    }
                },
                {
                    "/=",[this](Thing *arg) {
                        assert(arg!=NULL && arg->rhizome_type()==rhizome_type());
                        Float *f = (Float*)arg;
                        value /= f->value;
                        return (Thing*)this;
                    }
                }
            });

            dispatcher.at(method)(arg);

            stringstream err;
            err << "Unknown Decimal method: " << method << ".\n"; 
            if(context!=NULL) {
                err << "    Context: ";
                context->serialize_to(err);
            }
            throw runtime_error(err.str());
        }

        long double
        Float::get_value() const {
            return value;
        }
    }
}