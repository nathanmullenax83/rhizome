#ifndef RHIZOME_HTML_ARTICLE_HPP
#define RHIZOME_HTML_ARTICLE_HPP

#include <iostream>
#include "element.hpp"
#include "container.hpp"

using std::ostream;

namespace rhizome {
    namespace html {
        class Article: public Element, public Container {
        public: 
            Article();
            ~Article();

            virtual void write_to( ostream &out );
            virtual bool has_interface( string const &name ) override;
        };
    }
}

#endif