#ifndef RHIZOME_HTML_THEAD_HPP
#define RHIZOME_HTML_THEAD_HPP

#include <iostream>
#include <vector>
#include "element.hpp"
#include "container.hpp"
#include "tr.hpp"
#include "th.hpp"


using std::ostream;
using std::vector;

namespace rp = rhizome::pattern;

namespace rhizome {
    namespace html {
        class THead: public Element, public Container {
        private:
            Tr row;
        public:
            THead();
            ~THead();

            // element interface
            virtual void write_to( ostream &out );

            virtual void serialize_to( ostream &out ) const override;
            // virtual void deserialize_from( istream &in, IParser *parser ) override;

            // Thing requires:
            // virtual rp::Pattern * make_pattern() const override;
            // virtual rp::Pattern * make_concise_pattern() const override;

            // thead-specific
            void add_column( string const &name );
            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;

        };
    }
}

#endif