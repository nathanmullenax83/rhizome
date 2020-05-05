#ifndef RHIZOME_HTML_HEAD
#define RHIZOME_HTML_HEAD

#include <iostream>
#include "element.hpp"
#include "container.hpp"
#include "title.hpp"

namespace rp = rhizome::pattern;

using std::ostream;

namespace rhizome {
    namespace html {
        class Head: public Element, public Container {
        public:
            Head();
            ~Head();

            virtual void write_to( ostream &out );
            Title & title(string const &t);

            // virtual rp::Pattern * make_pattern() const override;
            // virtual rp::Pattern * make_concise_pattern() const override;

            virtual void serialize_to( ostream &out ) const override;
            // virtual void deserialize_from( istream &in, IParser *parser ) override;

            virtual Thing * clone() const;
            virtual string rhizome_type() const override;

            virtual bool has_interface( string const &name ) override;
        };
    }
}

#endif