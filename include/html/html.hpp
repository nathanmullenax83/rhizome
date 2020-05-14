#ifndef RHIZOME_HTML_HPP
#define RHIZOME_HTML_HPP

#include <iostream>
#include <sstream>
#include <string>

using std::stringstream;
using std::ostream;
using std::string;

#include "core/thing.hpp"
#include "element.hpp"
#include "head.hpp"
#include "body.hpp"
#include "title.hpp"

using rhizome::core::Thing;

namespace rp = rhizome::pattern;

namespace rhizome {
    namespace html {
        class HTML: public Element {
        public:
            Head head;
            Body body;
        
            HTML();
            HTML( string const &title );
            virtual ~HTML();
            
            virtual void write_to( ostream &out );
            
            // virtual rp::Pattern * make_pattern() const override;
            // virtual rp::Pattern * make_concise_pattern() const override;

            virtual void serialize_to( ostream &out ) const override;
            // virtual void deserialize_from( istream &in, IParser *parser ) override;

            virtual Thing * clone() const;
            virtual string rhizome_type() const override;

            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;
        };
    }
}

#endif
