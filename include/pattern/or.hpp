#ifndef RHIZOME_PATTERN_OR
#define RHIZOME_PATTERN_OR

#include "pattern.hpp"
#include <vector>

using std::vector;

namespace rhizome {
    namespace pattern {
        class Or: public Pattern {
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
            
            
            virtual IPattern * clone_pattern() const;
            virtual void serialize_to( ostream &out ) const;

            virtual bool has_interface( string const &name ) override;
            virtual string rhizome_type() const override;

            
        };
    }
}

#endif