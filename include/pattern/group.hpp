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
            
        public:
            Group(IPattern *p);
            virtual ~Group();

            virtual void reset();
            virtual bool accepted() const;
            virtual void transition(char c);
            virtual bool can_transition(char c) const;

            
            virtual IPattern * clone_pattern(bool withstate) const override;
            virtual void serialize_to( size_t level, ostream &out ) const;

            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            virtual string rhizome_type() const override;
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;
        };
    }
}

#endif