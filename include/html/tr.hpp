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

            virtual void write_to( std::ostream &out, size_t indent ) const;
            virtual void serialize_to( size_t level, std::ostream &out ) const override;
            

            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
        };
    }
}

#endif