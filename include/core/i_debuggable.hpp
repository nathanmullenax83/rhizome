#ifndef RHIZOME_CORE_I_DEBUGGABLE_HPP
#define RHIZOME_CORE_I_DEBUGGABLE_HPP

#include <iostream>
#include <map>
#include <string>
#include "thing.hpp"

using std::ostream;
using std::map;

namespace rhizome {
    namespace core {
        class IDebuggable {
        public: 
            /// Show the state of this object.
            virtual void dump( std::ostream & ) const = 0;
            
        };

        
    }
}

#endif
