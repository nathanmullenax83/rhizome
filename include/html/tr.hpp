#ifndef RHIZOME_HTML_TR_HPP
#define RHIZOME_HTML_TR_HPP

#include <iostream>
#include <vector>
#include "element.hpp"
#include "container.hpp"
#include "td.hpp"

using std::ostream;
using std::vector;

namespace rp = rhizome::pattern;

namespace rhizome {
    namespace html {
        class Tr: public Element, public Container {
        private:
            vector<Td> cells;
        public:
            Tr();
            ~Tr();

            virtual void write_to( std::ostream &out, size_t indent );
            virtual void serialize_to( std::ostream &out ) const override;
            // virtual void deserialize_from( istream &in, IParser *parser ) override;
            // virtual rp::Pattern * make_pattern() const override;
            // virtual rp::Pattern * make_concise_pattern() const override;

            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;
        };
    }
}

#endif