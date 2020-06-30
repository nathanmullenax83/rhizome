#include "container.hpp"


namespace rhizome {
    namespace html {
        Container::Container() {

        }

        Container::~Container() {
            for(size_t i=0; i<children.size(); ++i) {
                delete children[i];
            }
        }

        vector<Element *> 
        Container::clone_children() const {
            vector<Element *> elems;
            for(size_t i=0; i<children.size(); ++i) {
                elems.push_back( (Element*)children[i]->clone() );
            }
            return elems;
        }

        void 
        Container::add_child( Element *e ) {
            children.push_back(e);
        }

        Element *
        Container::child_at( size_t index ) {
            return children[index];
        }

        void
        Container::write_children( ostream &out, size_t indent ) {
            for(size_t i=0; i<children.size();++i) {
                children[i]->write_to(out,indent+1);
            }
        }

        void
        Container::serialize_children( ostream &out ) const {
            for(size_t i=0; i<children.size();++i) {
                children[i]->serialize_to(out);
            }
        }

        H1 &
        Container::h1( string const &title ) {
            H1 *h1 = new H1(title);
            add_child(h1);
            return *h1;
        }
        /*
        P &
        Container::p( string const &cdata ) {
            P *p = new P(cdata);
            add_child(p);
            return *p;
        }*/

        UL &
        Container::ul() {
            UL *ul = new UL();
            add_child(ul);
            return *ul;
        }

        UL &
        Container::ul( function< void(UL&) > initialize_with) {
            UL *ul = new UL();
            add_child(ul);
            initialize_with(*ul);
            return *ul;
        }

    }
}