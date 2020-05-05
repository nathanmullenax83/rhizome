#ifndef RHIZOME_PATTERN_NAMED_GROUP
#define RHIZOME_PATTERN_NAMED_GROUP

#include <string>
#include "pattern.hpp"
#include "group.hpp"

using std::string;

namespace rhizome {
    namespace pattern {

        class NamedGroup: public Group {
        private:
            string name;
            IPattern *inner;
        public:
            NamedGroup(string const &name, IPattern *p);
            virtual ~NamedGroup();

            virtual bool has_interface( string const &name ) override;
            virtual string rhizome_type() const override;
            virtual IPattern * clone_pattern() const override;
        };
    }
}

#endif
