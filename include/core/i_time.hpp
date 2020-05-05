#ifndef RHIZOME_CORE_I_TIME_HPP
#define RHIZOME_CORE_I_TIME_HPP

#include <ctime>

using std::time_t;

namespace rhizome {
    namespace core {
        /// This is the interface for the time parameter of IFunction's 
        /// 'tick' (aka reduce?) method.
        class ITime {
        public:
            virtual time_t get() const = 0;
        };
    }
}

#endif
