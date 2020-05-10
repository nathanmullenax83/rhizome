#ifndef RHIZOME_PATTERN_ANY_HPP
#define RHIZOME_PATTERN_ANY_HPP

#include "pattern.hpp"
#include "cclass.hpp"


using rhizome::pattern::Pattern;

namespace rp = rhizome::pattern;

namespace rhizome {
    namespace pattern {
        class Any: public CClass {
        private:
            size_t state;
        public:
            Any();
            virtual ~Any();

            virtual void reset() override;
            virtual bool can_transition(char c) const;
            virtual void transition(char c) override;
            virtual bool accepted() const;

            virtual IPattern * clone_pattern() const;
            virtual void serialize_to( ostream &out ) const;
            virtual void serialize_to_cclass_context( ostream &out ) const;

            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;
            virtual string rhizome_type() const override;
        };
    }
}

#endif
