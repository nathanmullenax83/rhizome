#ifndef RHIZOME_PATTERN_CHARS_HPP
#define RHIZOME_PATTERN_CHARS_HPP

#include <set>
#include <string>
#include <cassert>
#include "cclass.hpp"

using std::string;
using std::set;

namespace rhizome {
    namespace pattern {
        /// Pattern for a set of characters, constructed as a string.
        class Chars: public CClass {
        private:
            set<unsigned long long> cs;
            size_t state;

        public:
            Chars();
            Chars( string const &cees );

            virtual string rhizome_type() const override;
            
            virtual bool has_interface( string const &w ) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;

            virtual void serialize_to( std::ostream &out ) const override;
            virtual void serialize_to_cclass_context( std::ostream &out ) const override;
            virtual IPattern * clone_pattern(bool withstate) const override;

            virtual bool can_transition(char c) const override;
            virtual void transition(char c) override;
            virtual bool accepted() const override;
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;
            virtual void reset() override;

        };
    }
}

#endif
