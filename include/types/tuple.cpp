#include "tuple.hpp"

namespace rhizome {
    namespace types {
        Tuple::Tuple() {

        }

        Tuple::~Tuple() {
            for(size_t i=0; i<items.size(); ++i) {
                delete items[i];
                items[i] = NULL;
            }
        }

        vector<string>
        Tuple::get_vector_of_native_strings() {
            vector<string> vs;
            for(size_t i=0; i<items.size(); ++i) {
                stringstream e;
                items[i]->serialize_to(e);
                vs.push_back(e.str());
            }
            return vs;
        }

        Thing *
        Tuple::clone() const {
            Tuple *copy = new Tuple();
            for(size_t i=0; i<items.size(); ++i) {
                copy->append( items[i]->clone() );
            }
            return copy;
        }

        void 
        Tuple::serialize_to( ostream &out ) const {
            out << "(";
            for(size_t i=0; i<items.size();++i) {
                items[i]->serialize_to(out);
                if( i < items.size()-1) {
                    out << ",";
                }
            }
            out << ")";
        }

        string
        Tuple::rhizome_type() const {
            stringstream tn;
            for(size_t i=0; i<items.size();++i) {
                tn << items[i]->rhizome_type();
                if( i < items.size()-1 ) {
                    tn << '*';
                }
            }
            return tn.str();
        }


        void Tuple::append( Thing *thing ) {
            items.push_back(thing);
        }

        void Tuple::prepend( Thing *thing ) {
            items.push_front(thing);
        }

        Thing * Tuple::at( size_t i ) {
            return items.at(i);
        }

        bool
        Tuple::has_interface(string const &w) {
            return (w==rhizome_type()||w=="Thing");
        }

        Thing *
        Tuple::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)context;
            if( arg != NULL ) {
                if( method=="append" ) {
                    append( arg );
                } else if( method=="prepend") {
                    prepend(arg);
                }
            }
            throw runtime_error("Nothing to invoke.");
        }

        size_t Tuple::size() const { return items.size(); }

        Thing *
        Tuple::extract_first() {
            assert( items.size() > 0);
            Thing *f = items.front();
            items.pop_front();
            return f;
        }

        Thing *
        Tuple::extract_last() {
            assert( items.size() > 0);
            Thing *f = items.back();
            items.pop_back();
            return f;
        }

    }
}