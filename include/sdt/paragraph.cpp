#include "paragraph.hpp"

namespace rhizome {
    namespace sdt {

        Paragraph::Paragraph() {

        }

        string Paragraph::HumanName() const {
            return "paragraph";
        }

        string Paragraph::InternalName() const {
            return "rhizome::sdt::Paragraph";
        }

        string Paragraph::Text() const {
            return text;
        }
    }
}