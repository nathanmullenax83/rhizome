#ifndef RHIZOME_PATTERN_NONGREEDY
#define RHIZOME_PATTERN_NONGREEDY

#include "pattern.hpp"

using rhizome::pattern::Pattern;

namespace rhizome {
    namespace pattern {
        class NonGreedy: public Pattern {
        private:
            Pattern *inner;
        public:
            NonGreedy( Pattern *inner );
            virtual ~NonGreedy();

            virtual bool accepted() const;
            virtual void reset();
            virtual bool can_transition(char c) const;
            virtual void transition(char c);
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;

            // thing interface
            virtual void serialize_to(size_t level, ostream &out ) const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg) override;
            virtual string rhizome_type() const override;
            virtual Thing * clone() const override;

            virtual Pattern * clone_pattern(bool withstate) const override;  
        };
    }
}

#endif
