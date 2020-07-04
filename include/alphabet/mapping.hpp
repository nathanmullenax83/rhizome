#ifndef RHIZOME_ALPHABET_MAPPING_HPP
#define RHIZOME_ALPHABET_MAPPING_HPP

#include <codecvt>
#include <locale>
#include <cwchar>
#include <cwctype>
#include <map>
#include <string>

#include "core/thing.hpp"
#include "types/tuple.hpp"
#include "types/char.hpp"

using std::map;
using std::string;
using std::wstring;
using rhizome::core::Thing;
using rhizome::types::Tuple;
using rhizome::types::Char;

namespace rhizome {
    namespace alphabet {
        wstring widen( string const &s );


        /// Class for mapping (unicode) characters to other characters.
        class Mapping: public Thing {
        private:
            map<wchar_t, wchar_t> mapping;
        public:
            Mapping();

            void define_map_char( wchar_t from, wchar_t to );
            void define_map_range( wchar_t src, wchar_t dest, size_t width );

            /// Simple, single wide character mapping.
            wchar_t lookup( wchar_t c );

            /// Widen, translate, utf8 encode and return!
            string to_chars( string const &s );
            /// translate, utf8 encode and return
            string to_chars( wstring const &s );

                  

            virtual void serialize_to( std::ostream &out ) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing * arg ) override;
        };
    }
}

#endif