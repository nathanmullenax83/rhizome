#ifndef RHIZOME_PATTERN_CCLASS_UNION 
#define RHIZOME_PATTERN_CCLASS_UNION

#include <vector>
#include <stdexcept>

#include "cclass.hpp"

using std::vector;
using std::runtime_error;

namespace rhizome {
    namespace pattern {
        /// represents a superset of several character classes.
        class CClassUnion: public CClass {
        private:
            vector<CClass *> parts;
            size_t state;
        public:
            CClassUnion();

            void add_part( CClass *cls );

            virtual void reset();
            virtual bool can_transition(char c) const override;
            virtual void transition(char c) override; 
            virtual bool accepted() const;

            virtual IPattern * clone_pattern(bool withstate) const;
            virtual void serialize_to( ostream &out ) const;
            virtual void serialize_to_cclass_context( ostream &out ) const;

            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;
        };
    }
}

#endif