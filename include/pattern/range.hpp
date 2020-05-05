#ifndef RHIZOME_PATTERN_RANGE
#define RHIZOME_PATTERN_RANGE

#include "pattern.hpp"
#include "cclass.hpp"

namespace rhizome {
    namespace pattern {
        class Range : public CClass {
        private:
            char from;
            char to;
            size_t state;
        public:        
            Range( char from, char to );

            virtual bool accepted() const ;
            virtual void transition(char c);
            virtual bool can_transition(char c) const;
            virtual void reset();
            virtual IPattern * clone_pattern() const override;
            virtual void serialize_to( ostream &out ) const;
            virtual void serialize_to_cclass_context( ostream &out ) const;

            virtual bool has_interface( string const &name ) override;
            virtual string rhizome_type() const override;
        };
    }
}

#endif
