#ifndef RHIZOME_CORE_VERIFIABLE_HPP
#define RHIZOME_CORE_VERIFIABLE_HPP

#include <iostream>

using std::ostream;


namespace rhizome {
    namespace core {
        /// Implement this class to attach module testing to a class
        class IVerifiable {
        public:

            virtual bool verify( std::ostream &summary ) = 0;
            static bool assertion( std::ostream &out, bool condition, string const &what ) {
                if( condition ) {
                    out << "\033[1;32m"<< "Passed    " << "\033[0m";
                } else {
                    out << "\033[1;31m" << "Failed    " << "\033[0m";
                }
                out << what << "\n";
                return condition;
            };
        };
    }
}

#endif
