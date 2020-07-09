#ifndef RHIZOME_HTML_TABLE
#define RHIZOME_HTML_TABLE
#include <iostream>

#include "element.hpp"
#include "container.hpp"
#include "thead.hpp"
#include "tbody.hpp"

using std::ostream;

namespace rhizome {
    namespace html {
        class Table: public Element, public Container {
        private:
            THead thead;
            TBody tbody;

        public:
            Table();
            ~Table();

            virtual void write_to( ostream &out, size_t indent ) const;
            virtual void serialize_to( size_t level,ostream &out ) const;
        };
    }
}

#endif
