#ifndef RHIZOME_PATTERN_ALPHA_HPP
#define RHIZOME_PATTERN_ALPHA_HPP

#include <cctype>
#include <stdexcept>
#include "cclass.hpp"

using std::isalpha;
using std::runtime_error;

namespace rhizome {
    namespace pattern {
        class Alpha: public CClass {
        private:
            size_t state;
            
        public:
            Alpha();

            virtual void reset();
            virtual bool can_transition(char c) const;
            virtual void transition(char c) override;
            virtual bool accepted() const;

            virtual IPattern * clone_pattern(bool withstate) const;
            virtual void serialize_to( size_t level, ostream &out ) const;
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
