#ifndef RHIZOME_CORE_I_TOKEN
#define RHIZOME_CORE_I_TOKEN

#include <string>

using std::string;

namespace rhizome {
    namespace core {
        class IToken {
        public:
            virtual void set( string const &tvalue, string const &tname, size_t line_no, size_t col) = 0;

            virtual size_t line() const = 0;
            virtual size_t column() const = 0;

            virtual string token_value() const = 0;
            virtual string token_class() const = 0;

            
            
        };
    }
}

#endif
