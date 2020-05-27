#ifndef RHIZOME_PATTERN_BEGINNING
#define RHIZOME_PATTERN_BEGINNING

#include <string>
#include <stdexcept>
#include "pattern.hpp"

using std::string;
using std::runtime_error;

namespace rhizome {
    namespace pattern {
        class Beginning: public Pattern {
        private:
            size_t state;
        public:
            Beginning();

            virtual void reset();
            virtual void transition(char c) override;
            virtual bool can_transition(char c) const;

            /// Starts out in 'accept'. 
            virtual bool accepted() const;

            virtual IPattern * clone_pattern(bool withstate) const override;
            virtual void serialize_to( ostream &out ) const override;

            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;
            virtual string rhizome_type() const override;
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;
        };
    }
}

#endif
