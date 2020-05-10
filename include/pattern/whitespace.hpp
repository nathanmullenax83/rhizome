#ifndef RHIZOME_PATTERN_WHITESPACE
#define RHIZOME_PATTERN_WHITESPACE

#include <cctype>
#include <stdexcept>
#include "cclass.hpp"

using std::runtime_error;

namespace rhizome {
    namespace pattern {

        /// Match a single whitespace
        class Whitespace: public CClass {
        private:
            size_t state;
        public:
            Whitespace();

            virtual void reset();
            virtual bool can_transition(char c) const;
            virtual void transition(char c);
            virtual bool accepted() const;

            virtual IPattern * clone_pattern() const override;
            virtual void serialize_to( ostream &out ) const;
            virtual void serialize_to_cclass_context( ostream &out ) const;

            virtual string rhizome_type() const override;
            virtual bool has_interface(string const &name) override;
            virtual Thing * invoke( string const &method, Thing * arg ) override;


        };
    }
}

#endif
