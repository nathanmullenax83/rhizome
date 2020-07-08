#include <cassert>
#include "char.hpp"

using rhizome::core::Dispatcher;

namespace rhizome {
    namespace types {
        namespace chars {
            static Dispatcher<Char> dispatcher({
                {
                    "evaluate",[]( Thing *context, Char *that, Thing *arg ) {
                        assert(arg==NULL);
                        return that->evaluate(context);
                    }
                }
            });

        }

        Char::Char(): v(0) {

        }

        Char::Char( wchar_t v): v(v) {

        }

        string
        Char::rhizome_type() const {
            return "Char";
        }

        bool
        Char::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }

        void
        Char::serialize_to( std::ostream &out ) const {
            out << v;
        }

        Thing *
        Char::clone() const {
            return new Char(v);
        }

        Thing *
        Char::invoke( Thing *context, string const &method, Thing *arg ) {
            
            try {
                Thing *r = chars::dispatcher.at(method)(context,this,arg);
                return r;
            } catch(std::exception *e) {
                if( chars::dispatcher.count(method)==0) {
                    throw runtime_error(rhizome::core::invoke_method_not_found(method,this,context));
                } else {
                    throw runtime_error(rhizome::core::invoke_error(method,arg,this,context,e));
                }
            }
            
        }

        Thing *
        Char::evaluate( Thing *context ) const {
            (void)context;
            return clone();
        }
    }
}