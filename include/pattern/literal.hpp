#ifndef RHIZOME_PATTERN_LITERAL_HPP
#define RHIZOME_PATTERN_LITERAL_HPP

#include <string>
#include <iostream>
#include "pattern.hpp"

using std::string;
using std::ostream;

namespace rhizome {
    namespace pattern {
        class Literal: public Pattern {
        private:
            string w;
            size_t state;

        public:
            Literal( string const &w );
            virtual void transition(char c) override;
            virtual void reset() override;

            virtual bool can_transition(char c) const;
            virtual bool accepted() const;
            
            virtual IPattern * clone_pattern(bool withstate) const override;
            virtual void serialize_to( ostream &out ) const;

            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;
        };
    }
}

#endif
