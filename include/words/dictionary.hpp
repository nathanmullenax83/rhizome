#ifndef RHIZOME_WORDS_DICTIONARY_HPP
#define RHIZOME_WORDS_DICTIONARY_HPP

#include <map>
#include <string>
#include <tuple>
#include "types/integer.hpp"

using rhizome::types::Integer;
using std::map;
using std::string;
using std::pair;

#include "core/thing.hpp"

using rhizome::core::Thing;

namespace rhizome {
    namespace words {
        /// encoding table for words
        class Dictionary: public Thing {
        private:
            /// string: count*position
            map< string, pair<size_t,size_t> > counts;
            size_t current_id;
            /// Update the table 
            
            
            /// compute number of bits needed to specify a 
            /// member of this dictionary
            
        public:
            Dictionary();
            ~Dictionary();
            void update_table();
            Integer id( string const &s );

            size_t bits() const;

            virtual void serialize_to( size_t level, std::ostream &out ) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * clone() const override;
            virtual Thing * invoke ( Thing *context, string const &method, Thing *arg ) override;

        };
    }
}

#endif