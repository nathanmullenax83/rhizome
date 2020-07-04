#ifndef RHIZOME_TYPES_CHAR_HPP
#define RHIZOME_TYPES_CHAR_HPP

#include <string>
#include <stdexcept>
#include <cwchar>
#include <map>
#include <tuple>
#include <cwctype>
#include "core/thing.hpp"

using std::string;
using std::runtime_error;
using std::pair;
using std::map;

using rhizome::core::Thing;

namespace rhizome {
    namespace types {
        class Char: public Thing {
        public:
            wchar_t v;
            Char();
            Char(wchar_t v);

            virtual void serialize_to( std::ostream &out ) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * clone() const override;

            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
        };

        
    }
}

#endif
