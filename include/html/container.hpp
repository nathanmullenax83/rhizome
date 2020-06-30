#ifndef RHIZOME_HTML_CONTAINER_HPP
#define RHIZOME_HTML_CONTAINER_HPP

#include <vector>
#include <iostream>
#include <functional>
#include "element.hpp"
#include "h1.hpp"

#include "ul.hpp"

using std::vector;
using std::ostream;
using std::function;

namespace rhizome {
    namespace html {
        class Container {
        protected:
            vector<Element *> children;
            vector<Element *> clone_children() const;
        public:
            Container();
            virtual ~Container();

            void add_child( Element *e );
            Element * child_at( size_t index );

            void write_children( ostream &out, size_t indent );
            void serialize_children( ostream &out ) const;

            H1 & h1( string const &title );
            //P & p( string const &cdata );
            UL & ul();
            UL & ul( function< void (UL &) > initialize_with );

            

            
        };
    }
}

#endif
