#ifndef RHIZOME_TYPES_TYPE_CONSTRAINT
#define RHIZOME_TYPES_TYPE_CONSTRAINT

#include "core/thing.hpp"

using rhizome::core::Thing;

namespace rhizome {
    namespace types {
        /// Abstract TypeConstraint. Subclasses enforce arbitrary parametric types.
        /// For instance:
        ///     TypeIs checks for a single, concrete type
        ///     HasInterface checks for implementation of an interface via invoke.
        ///     
        class TypeConstraint: public Thing {
        public:

            virtual bool contains( Thing *t ) const =  0;
        };
    }
}

#endif