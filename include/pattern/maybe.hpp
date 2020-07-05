#ifndef RHIZOME_PATTERN_MAYBE_HPP
#define RHIZOME_PATTERN_MAYBE_HPP
#include <cassert>
#include "pattern.hpp"
#include "types/string.hpp"

using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        class Maybe: public Pattern  {
        private:
            IPattern *inner;
        public:
            Maybe( IPattern *inner );
            ~Maybe();

            virtual void reset();
            virtual bool can_transition(char c) const;
            virtual void transition(char c);
            virtual bool accepted() const;

            virtual IPattern * clone_pattern(bool withstate) const override;
            virtual void serialize_to( ostream &out ) const;

            virtual bool has_interface( string const &name ) override;
            
            virtual string rhizome_type() const override;

            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;

            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
        };

        Maybe * maybe( IPattern *inner );
        
    }
}

#endif
