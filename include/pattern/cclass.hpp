#ifndef RHIZOME_PATTERN_CCLASS_HPP
#define RHIZOME_PATTERN_CCLASS_HPP

#include "pattern.hpp"

namespace rhizome {
    namespace pattern {
        /// Character class represents a set of characters
        class CClass : public Pattern {
        public:
            /// Sometimes you don't need square braces.
            virtual void serialize_to_cclass_context( ostream &out ) const = 0;
            
        };
    }
}

#endif
