#ifndef RHIZOME_HTML_UL
#define RHIZOME_HTML_UL

#include <vector>
#include <iostream>
#include "pattern.hpp"
#include "element.hpp"
#include "li.hpp"

using std::ostream;
using std::vector;

using rhizome::pattern::Pattern;

namespace rhizome {
    namespace html {
        /// Represents an unordered list.
        class UL: public Element  {
        private:
            vector<LI> items;
        public:
            UL();
            ~UL();

            virtual void write_to( ostream &out, size_t indent ) const;
            virtual void serialize_to( size_t level, ostream &out ) const override;
            // virtual void deserialize_from( istream &in, IParser *parser ) override;

            LI & li( string const &contents );

            // virtual Pattern * make_pattern() const override;
            // virtual Pattern * make_concise_pattern() const override;

            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;
            virtual Thing * invoke(Thing *context,  string const &method, Thing * arg ) override;
        };
    }
}

#endif
