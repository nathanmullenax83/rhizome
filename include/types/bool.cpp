#include "bool.hpp"
#include <cassert>

using rhizome::core::Dispatcher;

namespace rhizome {
    namespace types {
        namespace bools {
            static Dispatcher<Bool> dispatcher({
                {
                    "!",[]( Thing *context, Bool *that, Thing * arg ) {
                        (void)context;
                        assert(arg==NULL);
                        return (Thing*)new Bool(!that->value);
                    }
                },
                {
                    "=",[]( Thing *context, Bool *that, Thing * arg ) {
                        (void)context;
                        assert(arg!=NULL && arg->rhizome_type()==that->rhizome_type());
                        that->value = ((Bool*)arg)->value;
                        return that;
                    }
                },
                {
                    "===",[]( Thing *context, Bool *that, Thing * arg ) {
                        (void)context;
                        assert(arg!=NULL && arg->rhizome_type()==that->rhizome_type());
                        Bool *b = (Bool*)arg;
                        return (Thing*)new Bool(that->value==b->value);
                    }
                },
                {
                    "&=",[]( Thing *context, Bool *that, Thing * arg ){
                        (void)context;
                        assert(arg!=NULL && arg->rhizome_type()==that->rhizome_type());
                        Bool *b = (Bool*)arg;
                        that->value = that->value && b->value;
                        return that;
                    }
                },
                {
                    "|=",[]( Thing *context, Bool *that, Thing * arg ){
                        (void)context;
                        assert(arg!=NULL && arg->rhizome_type()==that->rhizome_type());
                        Bool *b = (Bool*)arg;
                        that->value = that->value || b->value;
                        return that;
                    }
                },
                {
                    "⊕=",[]( Thing *context, Bool *that, Thing * arg ) {
                        (void)context;
                        assert(arg!=NULL && arg->rhizome_type()==that->rhizome_type());
                        Bool *b = (Bool*)arg;
                        that->value = that->value ^ b->value;
                        return that;
                    }
                }
            });
        }


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
        Bool::invoke( Thing *context, string const &method, Thing *arg ) {

            try {
                Thing *r = bools::dispatcher.at(method)(context,this,arg);
                return r;
            } catch( std::exception *e ) {
                stringstream err;
                err << "Bool dispatcher does not contain the method '" << method << ".\n";
                if( context != NULL ) {
                    err << "Context: ";
                    context->serialize_to(err);
                }
                throw runtime_error(err.str());
            }
        }

        Thing *
        Bool::evaluate( Thing *context ) const {
            (void)context;
            return clone();
        }
    }
}