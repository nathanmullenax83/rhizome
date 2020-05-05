#ifndef RHIZOME_PATTERN_GROUP
#define RHIZOME_PATTERN_GROUP

#include <sstream>
#include <string>
#include "pattern.hpp"
#include "core/i_pattern.hpp"

using std::stringstream;
using std::string;

namespace rhizome {
    namespace pattern {
        class Group: public Pattern {
        protected:
            IPattern *inner;
            stringstream _captured;
        public:
            Group(IPattern *p);
            virtual ~Group();

            virtual void reset();
            virtual bool accepted() const;
            virtual void transition(char c);
            virtual bool can_transition(char c) const;

            virtual string captured() const;
            virtual IPattern * clone_pattern() const override;
            virtual void serialize_to( ostream &out ) const;

            virtual bool has_interface( string const &name ) override;
            virtual string rhizome_type() const override;
        };
    }
}

#endif