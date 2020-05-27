#include "named_group.hpp"

namespace rhizome {
    namespace pattern {
        NamedGroup::NamedGroup( string const &name, IPattern *p ): name(name), inner(p) {

        }

        

        NamedGroup::~NamedGroup() {
            delete inner;
        }

        IPattern *
        NamedGroup::clone_pattern() const {
            NamedGroup *copy = new NamedGroup(name,inner->clone_pattern());
            return copy;
        }

        string
        NamedGroup::rhizome_type() const {
            return "pattern::NamedGroup";
        }

        bool
        NamedGroup::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="Thing";
        }
    }
}