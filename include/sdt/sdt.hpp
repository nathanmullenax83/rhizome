#ifndef RHIZOME_SDT_SDT_HPP
#define RHIZOME_SDT_SDT_HPP

#include <string>

using std::string;

namespace rhizome {
    namespace sdt {
        /// This namespace is for classes which directly represent some
        /// tangible thing, usually a document.
        class SDT {
        public:
            /// Return a 'friendly' name for this type. Please
            /// reserve capital letters for proper nouns and acronyms.
            virtual string HumanName() const = 0;

            /// Return the fully namespace-qualified name of the instance class.
            virtual string InternalName() const = 0;
        };
    }
}

#endif