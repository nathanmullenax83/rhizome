#ifndef RHIZOME_PATTERN_STAR_HPP
#define RHIZOME_PATTERN_STAR_HPP

#include "pattern.hpp"

namespace rhizome {
    namespace pattern {
        class Star: public Pattern {
        private:
            IPattern *inner;
            size_t match_count;
            stringstream xd;
        public:
            Star( IPattern *inner );
            virtual ~Star();

            virtual void reset() override;
            virtual void transition(char c) override;
            virtual bool can_transition(char c) const override;
            virtual bool accepted() const;

            virtual IPattern * clone_pattern(bool withstate) const override;
            virtual void serialize_to( ostream &out ) const;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;
            

        };
    }
}

#endif
