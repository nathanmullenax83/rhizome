#include "store.hpp"

namespace rhizome {
    namespace store {
        Store::Store(string const &path): root(path) {

        }

        Store::~Store() {

            for(auto i=data.begin(); i!=data.end(); i++) {
                ofstream obj;
                stringstream fname;
                fname << root.prefix() << "/" << i->first << "." << i->second->rhizome_type();
                obj.open(fname.str(), std::ofstream::trunc | std::ofstream::out );
                i->second->serialize_to(obj);
                obj.close();
            }
        }

        void
        Store::serialize_to( ostream &out ) const {
            out << rhizome_type() << "(";
            for( auto it=data.begin(); it!= data.end(); ++it) {
                out << it->first << ":";
                it->second->serialize_to(out);
                auto whu = it;
                if( ++whu != data.end() ) {
                    out << ";";
                }
            }
            out << ")";
        }

        Thing *
        Store::retrieve( string const &name ) {
            if( data.count(name)==0 ) {
                throw new runtime_error("Thing does not exist.");
            }
            return data[name];
        }

        void
        Store::set( string const &name, Thing *thing ) {
            if( data.count(name) ) {
                delete data[name];
            }
            data[name] = thing;
        }

        Thing * 
        Store::clone() const {
            Store *s2 = new Store( root.prefix() );
            for( auto i=data.begin(); i!=data.end(); ++i) {
                s2->set( i->first, i->second->clone() );
            }
            return s2;
        }

        string
        Store::rhizome_type() const {
            return "Store";
        }

        bool
        Store::has_interface( string const &name ) {
            return name==rhizome_type() || name=="Thing";
        }

        bool
        Store::exists( string const &name ) const {
            return data.count(name) > 0;
        }

        void
        Store::remove( string const &name ) {
            if( data.count(name) > 0 ) {
                delete data[name];
                data.erase(name);
            }
            
        }

        Thing *
        Store::get( string const &name ) {
            if( exists(name) ) {
                return data.at(name);
            } else {
                throw runtime_error("Element not defined.");
            }
        }

        Thing *
        Store::get_clone( string const &name ) const {
            if( exists(name) ) {
                return data.at(name)->clone();
            } else {
                throw runtime_error("Element not defined.");
            }
        }
    }
}