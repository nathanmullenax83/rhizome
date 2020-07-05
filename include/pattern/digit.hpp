#ifndef RHIZOME_PATTERN_DIGIT_HPP
#define RHIZOME_PATTERN_DIGIT_HPP

#include <cctype>
#include "pattern.hpp"
#include "cclass.hpp"

namespace rp = rhizome::pattern;

using std::isdigit;
using rhizome::pattern::CClass;
using rhizome::pattern::Pattern;


namespace rhizome {
    namespace pattern {
        /// Match any single digit (base 10)
        class Digit: public CClass {
        private:
            size_t state;
        public:
            Digit();
            virtual ~Digit();

            virtual bool can_transition(char c) const;
            virtual void transition(char c) override;
            virtual bool accepted() const;
            virtual void reset();

            virtual IPattern *clone_pattern(bool withstate) const override;
            virtual void serialize_to( ostream &out ) const;
            virtual void serialize_to_cclass_context( ostream &out ) const;

            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;

            virtual string rhizome_type() const override;
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;
        };
    }
}

#endif
