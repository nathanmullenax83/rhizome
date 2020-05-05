#ifndef RHIZOME_HTML_ELEMENT
#define RHIZOME_HTML_ELEMENT

#include <iostream>
#include <map>
#include <string>
#include "core/thing.hpp"


using std::ostream;
using std::string;
using std::map;

using rhizome::core::Thing;


namespace rhizome {
    namespace html {
        class Element: public Thing {
        protected:
            map<string,string> attributes;
        public:
            virtual ~Element();
            /// accessor for attributes.
            string & operator[] ( string const &attr_name );

            

            virtual void write_to( ostream &out )=0;
            

            virtual bool has_interface( string const &name ) override;
        };
    }
}

#endif