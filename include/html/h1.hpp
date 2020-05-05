#ifndef RHIZOME_HTML_H1_HPP
#define RHIZOME_HTML_H1_HPP

#include <stdexcept>
#include <iostream>
#include <string>
#include "element.hpp"
#include "pattern.hpp"

using std::ostream;
using std::runtime_error;

using rhizome::pattern::Pattern;

namespace rhizome {
    namespace html {
        class H1: public Element {
        private:
            string title;
        public:
            H1();
            explicit H1(string const &title);
            ~H1();

            virtual void write_to( ostream &out );
            
            virtual void serialize_to( ostream &out ) const override;

            virtual Thing * clone() const;
            virtual string rhizome_type() const override;

            virtual bool has_interface( string const &name ) override;
        };
    }
}

#endif