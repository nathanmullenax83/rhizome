#ifndef RHIZOME_TYPES_FLOAT
#define RHIZOME_TYPES_FLOAT
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "core/thing.hpp"
#include "types/expression.hpp"

using std::ostream;
using std::stringstream;
using std::runtime_error;
using rhizome::core::Thing;
using rhizome::core::Dispatcher;
using rhizome::types::Expression;

namespace rhizome {
    namespace types {
        class Float: public Expression {
        public:
            long double value;
            Float();
            Float( long double value );
            Float( string const &v );
            
            friend ostream & operator << ( ostream &out, Float const &j );

            virtual void serialize_to( size_t level, ostream &out ) const override;
            // virtual void deserialize_from( istream &in, IParser *parser ) override;
            virtual Thing * clone() const;
            virtual string rhizome_type() const override;
            virtual bool has_interface(string const &name) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;

            long double get_value() const;

            // expression interface
            virtual Thing * evaluate( Thing *context ) const override;
        };
    }
}

#endif
