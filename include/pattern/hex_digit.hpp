#ifndef RHIZOME_PATTERN_HEX_HPP
#define RHIZOME_PATTERN_HEX_HPP
#include <cctype>
#include <stdexcept>
#include "cclass.hpp"

using std::isdigit;
using std::runtime_error;

namespace rhizome {
    namespace pattern {
        class HexDigit: public CClass {
        private:
            size_t state;
        public:
            HexDigit();
            virtual ~HexDigit();

            virtual void reset();
            virtual bool can_transition(char c) const;
            virtual void transition(char c) override;
            virtual bool accepted() const;

            virtual IPattern * clone_pattern() const;

            virtual void serialize_to_cclass_context( ostream &out ) const;
            virtual void serialize_to( ostream &out ) const;

            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
        };
    }
}

#endif
