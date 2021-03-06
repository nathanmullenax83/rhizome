#ifndef RHIZOME_PATTERN_PLUS
#define RHIZOME_PATTERN_PLUS

#include <stdexcept>
#include "pattern.hpp"

using std::runtime_error;

namespace rhizome {
    namespace pattern {
        class Plus: public Pattern {
        private:
            IPattern *inner;
            size_t n_accepted;
            stringstream xd; // transformed input
        public:
            Plus( IPattern *inner );

            virtual void reset();
            virtual bool can_transition(char c) const;
            virtual void transition(char c);
            virtual bool accepted() const;

            virtual IPattern * clone_pattern(bool withstate) const override;
            virtual void serialize_to( size_t level, ostream &out ) const;

            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            virtual string rhizome_type() const override;
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;
        };

        Plus * plus( IPattern *inner );
    }
}

#endif
