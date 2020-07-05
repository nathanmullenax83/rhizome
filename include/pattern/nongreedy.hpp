#ifndef RHIZOME_PATTERN_NONGREEDY
#define RHIZOME_PATTERN_NONGREEDY

#include "pattern.hpp"

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

            virtual void serialize_to( ostream &out ) const;

            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg) override;
            virtual string rhizome_type() const override;
            virtual Pattern * clone() const override;
            
        };
    }
}

#endif
