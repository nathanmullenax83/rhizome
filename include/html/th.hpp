#ifndef RHIZOME_HTML_TH_HPP
#define RHIZOME_HTML_TH_HPP

#include <iostream>
#include <string>
#include "element.hpp"
#include "container.hpp"

using std::ostream;
using std::string;

namespace rp = rhizome::pattern;

namespace rhizome {
    namespace html {
        class Th: public Element, public Container {
        private:
            string cdata;
        public:
            Th(string const &text, string const &scope="col");
            ~Th();

            virtual void write_to( ostream &out, size_t indent );

            virtual void serialize_to( ostream &out ) const override;
            // virtual void deserialize_from( istream &in, IParser *parser ) override;
            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;

            // rp::Pattern * make_pattern() const override;
            // rp::Pattern * make_concise_pattern() const override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
        };
    }
}

#endif
