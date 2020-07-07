#include <cassert>
#include "string.hpp"
#include "types/char.hpp"

using rhizome::core::Dispatcher;
using rhizome::types::Char;

namespace rhizome {
    namespace types {
        namespace strings {
            static Dispatcher<String> dispatcher({
                {
                    "clone",[]( Thing *context, String *that, Thing *arg) {
                        (void)context;
                        assert( arg==NULL );
                        return that->clone();
                    }
                },
                {
                    "append",[]( Thing *context, String *that, Thing *arg) {
                        (void)context;
                        if( arg==NULL ) throw runtime_error("Expected something to append.");
                        if( arg->rhizome_type()=="String") {
                            // if appending a string, transform it to a native utf-8 string first.
                            String *sarg = (String*)arg;
                            that->append( sarg->native_string() );
                        } else {
                            // anything is appended using serialize_to method.
                            stringstream whatever;
                            arg->serialize_to(whatever);
                            that->append(whatever.str());
                        }
                        // in all cases return a pointer to the string that has been augmented.
                        return that;
                    }
                },
                {
                    "evaluate",[]( Thing *context, String *that, Thing *arg) {
                        assert(arg==NULL);
                        return that->evaluate(context);
                    }
                }
            });
        }

        String::String(): value("") {

        }

        String::String(string const&v): value(v) {

        }

        ostream & operator << ( ostream & out, String const &s ) {
            out << s.value;
            return out;
        }

        void
        String::serialize_to( ostream &out ) const {
            out << value;
        }

        Thing *
        String::clone() const {
            return new String(value);
        }

        string
        String::rhizome_type() const {
            return "String";
        }

        void 
        String::append( string const &w ) {
            stringstream ss;
            ss << value << w;
            value = ss.str();
        }

        bool
        String::has_interface(string const &w) {
            return (w==rhizome_type()||w=="Thing");
        }

        Thing *
        String::invoke( Thing *context, string const &method, Thing *arg ) {
            
            try {
                Thing *r = strings::dispatcher.at(method)(context,this,arg);
                return r;
            } catch (std::exception *e) {
                throw runtime_error(rhizome::core::invoke_error(method,arg, this,context,e));
            }

        }

        string
        String::native_string() const {
            return value;
        }

        Thing *
        String::evaluate( Thing *context ) const {
            (void)context;
            return clone();
        }
    }
}