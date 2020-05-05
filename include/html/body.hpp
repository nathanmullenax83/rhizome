#ifndef RHIZOME_HTML_BODY 
#define RHIZOME_HTML_BODY

#include <iostream>

using std::ostream;

#include "element.hpp"
#include "container.hpp"
#include "h1.hpp"
#include "p.hpp"

namespace rp = rhizome::pattern;

namespace rhizome {
    namespace html {
        class Body: public Element, public Container {
        public:
            Body();
            ~Body();

            virtual void write_to( ostream &out );
            virtual void serialize_to( ostream &out ) const override;
            // virtual void deserialize_from( istream &in, IParser *parser) override;
            
            // virtual rp::Pattern * make_pattern() const override;
            // virtual rp::Pattern * make_concise_pattern() const override;

            virtual Thing * clone() const;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            
        };
    }
}

#endif