#ifndef RHIZOME_PATTERN_WHITESPACE
#define RHIZOME_PATTERN_WHITESPACE

#include <cctype>
#include <stdexcept>
#include "cclass.hpp"
#include "core/i_verifiable.hpp"

using std::runtime_error;
using rhizome::core::IVerifiable;

namespace rhizome {
    namespace pattern {

        /// Match a single whitespace
        class Whitespace: public CClass, public IVerifiable {
        private:
            size_t state;
        public:
            Whitespace();

            virtual void reset();
            virtual bool can_transition(char c) const;
            virtual void transition(char c);
            virtual bool accepted() const;

            virtual IPattern * clone_pattern(bool withstate) const override;
            virtual void serialize_to( size_t level, ostream &out ) const override;
            virtual void serialize_to_cclass_context( ostream &out ) const override;

            virtual string rhizome_type() const override;
            virtual bool has_interface(string const &name) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing * arg ) override;

            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;
            
            virtual bool verify( std::ostream &out ) override;

        };
    }
}

#endif
