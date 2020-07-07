#ifndef RHIZOME_TYPES_STATEMENT
#define RHIZOME_TYPES_STATEMENT

#include "core/thing.hpp"
using rhizome::core::Thing;
using rhizome::core::Dispatcher;

namespace rhizome {
    namespace types {



        /// Statements /do/ have side effects.
        class Statement: public Thing {
        public:
            virtual Thing * evaluate( Thing *context ) = 0;
        };
    }
}

#endif