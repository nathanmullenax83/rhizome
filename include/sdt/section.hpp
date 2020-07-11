#ifndef RHIZOME_SDT_SECTION_HPP
#define RHIZOME_SDT_SECTION_HPP

#include <deque>

#include "core/thing.hpp"
#include "sdt.hpp"
#include "paragraph.hpp"

namespace rhizome {
    namespace sdt {
        class Section: public SDT {
        public:
            Section();

            virtual string HumanName() const override;
            virtual string InternalName() const override;
        };
    }
}

#endif
