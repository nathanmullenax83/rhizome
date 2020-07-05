#include "bool.hpp"
#include <cassert>

using rhizome::core::Dispatcher;

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
        Bool::invoke( Thing *context, string const &method, Thing *arg ) {
            static Dispatcher dispatcher({
                {
                    "!",[]( Thing *that, Thing * arg ) {
                        assert(arg==NULL);
                        return (Thing*)new Bool(!((Bool*)that)->value);
                    }
                },
                {
                    "=",[]( Thing *that, Thing *arg ) {
                        Bool *t = (Bool*)that;
                        assert(arg!=NULL && arg->rhizome_type()==t->rhizome_type());
                        ((Bool*)that)->value = ((Bool*)arg)->value;
                        return that;
                    }
                },
                {
                    "===",[]( Thing *that, Thing *arg ) {
                        Bool *t = (Bool*)that;
                        assert(arg!=NULL && arg->rhizome_type()==t->rhizome_type());
                        Bool *b = (Bool*)arg;
                        return (Thing*)new Bool(t->value==b->value);
                    }
                },
                {
                    "&=",[]( Thing *that, Thing *arg ) {
                        Bool *t = (Bool*)that;
                        assert(arg!=NULL && arg->rhizome_type()==t->rhizome_type());
                        Bool *b = (Bool*)arg;
                        t->value = t->value && b->value;
                        return that;
                    }
                },
                {
                    "|=",[]( Thing *that, Thing *arg ) {
                        Bool *t = (Bool*)that;
                        assert(arg!=NULL && arg->rhizome_type()==t->rhizome_type());
                        Bool *b = (Bool*)arg;
                        t->value = t->value || b->value;
                        return that;
                    }
                },
                {
                    "⊕=",[]( Thing *that, Thing *arg ) {
                        Bool *t = (Bool*)that;
                        assert(arg!=NULL && arg->rhizome_type()==t->rhizome_type());
                        Bool *b = (Bool*)arg;
                        t->value = t->value ^ b->value;
                        return that;
                    }
                }
            });
            try {
                Thing *r = dispatcher.at(method)(this,arg);
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
    }
}