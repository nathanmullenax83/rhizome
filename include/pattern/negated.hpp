#ifndef RHIZOME_PATTERN_NEGATED
#define RHIZOME_PATTERN_NEGATED

#include <string>
#include <sstream>
#include <stdexcept>

using std::string;
using std::stringstream;
using std::runtime_error;

#include "pattern.hpp"
#include "cclass.hpp"



namespace rhizome {
    namespace pattern {
        /// Negated character class
        class Negated: public CClass {
        private:
            CClass *inner;
            size_t n_accepted;
        public:
            Negated( CClass *inner );
            virtual ~Negated();
            // cclass::
            virtual void serialize_to_cclass_context( ostream &out ) const override;
            virtual void serialize_to( ostream &out ) const override;
            // pattern::
            virtual void transition( char c ) override;
            virtual bool can_transition( char c) const override;
            virtual bool accepted() const override;
            virtual void reset() override;
            

            virtual bool has_interface( string const &name ) override;
            virtual Thing *invoke( Thing *context, string const &method, Thing *arg ) override;
            virtual string rhizome_type() const override;
            virtual Pattern * clone_pattern(bool withstate) const override;
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;

        };
    }
}

#endif
