#ifndef RHIZOME_HTML_TITLE_HPP
#define RHIZOME_HTML_TITLE_HPP

#include <iostream>
#include "element.hpp"

using std::ostream;
using std::string;



namespace rhizome {
    namespace html {
        class Title: public Element {
        private:
            string cdata;
        public:
            Title();
            Title(string const &cdata);
            ~Title();

            virtual void write_to( ostream &out );
            
            virtual void serialize_to( ostream &out ) const override;
            // virtual void deserialize_from( istream &in, IParser *parser ) override;

            // virtual rp::Pattern * make_pattern() const override;
            // virtual rp::Pattern * make_concise_pattern() const override;

            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;
            
        };
    }
}

#endif
