#ifndef RHIZOME_SDT_PARAGRAPH_HPP
#define RHIZOME_SDT_PARAGRAPH_HPP

#include "core/thing.hpp"
#include "sdt.hpp"

namespace rhizome {
    namespace sdt {
        class Paragraph: public SDT {
        public:
            string text;

            Paragraph();

            virtual string HumanName() const override;
            virtual string InternalName() const override;
            
            virtual string Text() const;
        };
    }
}

#endif
