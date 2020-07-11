#ifndef RHIZOME_TYPES_THING
#define RHIZOME_TYPES_THING

#include <iostream>
#include <sstream>
#include <functional>
#include <map>
#include <set>
#include <vector>
#include <string>

using std::ostream;
using std::istream;
using std::stringstream;
using std::string;
using std::map;
using std::set;
using std::function;
using std::vector;
using std::string;

#include "i_token.hpp"

using rhizome::core::IToken;

namespace rhizome {
    namespace core {
        /// This is an abstract base class for representable objects. It could
        /// have been called Object, as it is in many computer languages. Or 
        /// noun, maybe.
        class Thing {
        public:
            

            /// Note: virtual destructor here so we can delete objects
            /// via thing pointers.
            virtual ~Thing() {};


            /// Describe the internal format of this object.
            virtual void serialize_to( size_t indent, ostream &out ) const = 0;
            //virtual void deserialize_from( istream &in, IParser *parser ) = 0;

            /// Deep clone of this object.
            virtual Thing * clone() const = 0;

            /// Internal type name. This is free-from for now, but I would suggest
            /// starting with a capital letter e.g., Integer. 
            virtual string rhizome_type() const = 0;

            /// In general, we need to be able to query an object for an interface.
            /// In anticipation of interfaces themselves being virtually constructed,
            /// all 'things' must implement has_interface. Notes:
            /// 1. This is a non-const method, so a 'thing' may construct an interface
            ///    upon request.
            virtual bool has_interface( string const &name ) = 0;

            virtual Thing * invoke( Thing * continuation, string const &method, Thing *argument ) = 0;
            


        };

        template< class T >
        using Dispatcher =  map< string, function< Thing*(Thing *,T*,Thing*) > >;

        string invoke_method_not_found( string const &method_name, Thing *on_object, Thing *context );
        string invoke_error( string const &method_name, Thing *arg, Thing *on_object, Thing *context, std::exception *e);
        
        /// Keep track of a handful of pointers. This might have function scope or class scope,
        /// but it is designed for functions to help keep marshalling functions from leaking 
        /// memory.
        class FreeList {
        public:
            set<Thing*> elems;

            FreeList();
            virtual ~FreeList();

            /// Add a pointer to the set.
            FreeList & operator+= (Thing *t);

            /// Add and pass a pointer
            Thing * operator() (Thing *t);

            /// This one takes some explaining, maybe.
            /// You can expressly free everything but return_value from this set.
            Thing * empty( Thing *return_value );
        };

        string indent( size_t level );
    }
}

#endif