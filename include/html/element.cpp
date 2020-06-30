#include "element.hpp"
#include "log.hpp"

namespace rhizome {
    namespace html {
        Element::~Element() {
            
        }

        string &
        Element::operator[]( string const &attr ) {
            // should be validated!
            return attributes[attr];
        }

        bool
        Element::has_interface( string const &name ) {
            return name==rhizome_type();
        }

        string
        Element::open_tag( string const &name ) {
            stringstream tag;
            tag << "<" << name;
            if( attributes.size() > 0 ) {
                for(auto i=attributes.begin(); i!= attributes.end(); i++) {
                    tag << " " << i->first << "=\"" << i->second << "\"";
                }
                
            }
            tag << ">";
            return tag.str();
        }
        
    }
}