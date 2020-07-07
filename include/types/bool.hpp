#ifndef RHIZOME_TYPES_BOOL_HPP
#define RHIZOME_TYPES_BOOL_HPP

#include <string>
#include <stdexcept>
#include "core/thing.hpp"
#include "expression.hpp"

using std::string;
using std::runtime_error;
using rhizome::core::Thing;


namespace rhizome {
    namespace types {
        class Bool: public Expression {
        public:
            bool value;
            Bool(bool value);

            // thing interface
            virtual void serialize_to(std::ostream &out) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * clone() const override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;

            // expression interface
            virtual Thing * evaluate( Thing *context ) const override;

        };
    }
}

#endif
