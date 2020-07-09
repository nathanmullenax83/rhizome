#ifndef RHIZOME_HTML_TBODY_HPP
#define RHIZOME_HTML_TBODY_HPP

#include <iostream>
#include <deque>
#include "element.hpp"
#include "container.hpp"
#include "tr.hpp"

using std::ostream;
using std::deque;

namespace rp = rhizome::pattern;

namespace rhizome {
    namespace html {
        class TBody: public Element, public Container {
        private:
            deque<Tr> rows;
        public:
            TBody();
            ~TBody();

            virtual void write_to( ostream &out, size_t indent ) const;
            virtual void serialize_to(size_t level, ostream &out ) const override;
            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;

            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;

        };
    }
}

#endif
