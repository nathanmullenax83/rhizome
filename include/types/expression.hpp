#ifndef RHIZOME_TYPES_EXPRESSION
#define RHIZOME_TYPES_EXPRESSION

#include "core/thing.hpp"

using rhizome::core::Thing;
using rhizome::core::Dispatcher;

namespace rhizome {
    namespace types {


        /// Expressions do not have side effects.
        class Expression: public Thing {
        public:
            virtual Thing * evaluate( Thing *context ) const = 0;

        };
    }
}

#endif