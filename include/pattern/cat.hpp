#ifndef RHIZOME_PATTERN_CAT_HPP
#define RHIZOME_PATTERN_CAT_HPP

#include <vector>
#include <cassert>
#include "pattern.hpp"

using std::vector;

namespace rhizome {
    namespace pattern {

        class Cat : public Pattern {
        private:
            vector<IPattern *> parts;
            size_t state;
        public:
            Cat();
            Cat( IPattern *a, IPattern *b );
            virtual ~Cat();

            void append( Pattern *p );

            virtual bool accepted() const;
            virtual void transition(char c) override;
            virtual bool can_transition(char c) const;
            virtual void reset();
            virtual IPattern * clone_pattern(bool withstate) const;
            virtual void serialize_to( size_t level,ostream &out ) const;

            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            virtual string rhizome_type() const override;
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;
        };

        Cat * cat( vector<IPattern*> const &parts );
    }
}

#endif
