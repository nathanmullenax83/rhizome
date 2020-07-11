#include "section.hpp"

namespace rhizome {
    namespace sdt {
        Section::Section() {

        }

        string
        Section::HumanName() const {
            return "section";
        }

        string
        Section::InternalName() const {
            return "rhizome::sdt::Section";
        }

        
    }
}