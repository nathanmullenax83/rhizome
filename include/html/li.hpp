#ifndef RHIZOME_HTML_LI_HPP
#define RHIZOME_HTML_LI_HPP

#include <iostream>
#include <string>
#include "pattern.hpp"
#include "element.hpp"

using std::ostream;
using std::string;
using rhizome::pattern::Pattern;

namespace rhizome {
    namespace html {
        class LI: public Element {
        private:
            string cdata;
        public:
            LI();
            LI(string const &cdata);
            ~LI();

            virtual void write_to( ostream &out, size_t indent );
            virtual void serialize_to( ostream &out ) const override;
            // virtual void deserialize_from( istream &in, IParser *parser ) override;

            // virtual Pattern * make_pattern() const override;
            // virtual Pattern * make_concise_pattern() const override;

            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;
        };
    }
}

#endif
