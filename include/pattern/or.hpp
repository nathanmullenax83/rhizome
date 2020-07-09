#ifndef RHIZOME_PATTERN_OR
#define RHIZOME_PATTERN_OR

#include "pattern.hpp"
#include "core/i_debuggable.hpp"
#include <vector>

using std::vector;
using rhizome::core::IDebuggable;

namespace rhizome {
    namespace pattern {
        class Or: public Pattern, public IDebuggable {
        private:
            vector< IPattern * > clauses;

            
        public:
            Or();
            Or( IPattern *left, IPattern *right );
            virtual ~Or();

            void add_clause( IPattern *p );

            virtual void reset();
            virtual void transition(char c) override;
            virtual bool can_transition(char c) const;
            virtual bool accepted() const;
            
            
            virtual IPattern * clone_pattern(bool withstate) const;
            virtual void serialize_to( size_t level,ostream &out ) const;

            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            virtual string rhizome_type() const override;
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;

            virtual void dump(std::ostream &out) const override;
        };
    }
}

#endif