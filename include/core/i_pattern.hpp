#ifndef RHIZOME_CORE_I_PATTERN
#define RHIZOME_CORE_I_PATTERN

#include <iostream>

using std::ostream;

namespace rhizome {
    namespace core {
        class IPattern {
        public:
            virtual ~IPattern() {}

            virtual void reset() = 0;
            virtual bool accepted() const = 0;
            /// true iff L(w)!
            virtual bool accepts( string const &w ) = 0;
            virtual void transition( char c ) = 0;
            virtual bool can_transition( char c ) const = 0;

            virtual void invalidate() = 0;
            virtual bool valid() const = 0;
            

            virtual IPattern * clone_pattern() const = 0;
            //virtual void serialize_to( ostream &out ) const = 0;
        };
    }
}

#endif
