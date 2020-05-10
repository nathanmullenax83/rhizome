#ifndef RHIZOME_TYPES_CHAR_HPP
#define RHIZOME_TYPES_CHAR_HPP

#include <string>
#include <stdexcept>
#include "core/thing.hpp"

using std::string;
using std::runtime_error;
using rhizome::core::Thing;

namespace rhizome {
    namespace types {
        class Char: public Thing {
        public:
            unsigned long long int v;
            Char();
            Char(unsigned long long int v);

            virtual void serialize_to( std::ostream &out ) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * clone() const override;

            virtual Thing * invoke( string const &method, Thing *arg ) override;
        };
    }
}

#endif
