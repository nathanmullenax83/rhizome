#include "store.hpp"


namespace P = rhizome::pattern;

namespace rhizome {
    namespace store {
        Store::Store(string const &path, IParser *p): root(path) {
            parser = p;
        }

        string compose_filename( string const &pfx, string const &varname, Thing *t) {
            stringstream f;
            f << pfx << "/" << varname << "." << t->rhizome_type();
            return f.str();
        }

        Store::~Store() {

            for(auto i=data.begin(); i!=data.end(); i++) {
                ofstream obj;
                stringstream fname;
                fname << root.prefix() << "/" << i->first << "." << i->second->rhizome_type();

                obj.open(
                    compose_filename(root.prefix(),i->first,i->second), 
                    std::ofstream::trunc | std::ofstream::out 
                );

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
        Store::lazy_load( string const &name ) {
            Parser *psr = (Parser*)parser;
            // get a list of files
            Pattern *p = P::cat({P::literal(name),new P::Star(new P::Any())}); 
            vector<string> fs = root.files( p );
            delete p;

            if( fs.size()==1) {
                ifstream f;
                f.open(fs[0], std::ifstream::in);
                psr->q_stream(f);
                stringstream c;
                for(size_t i=name.size()+2; i< fs[0].size(); ++i){
                    c.put(fs[0][i]);
                }
                return psr->parse_thing(c.str());
            } else {
                Tuple *t = new Tuple();
                for(size_t i=0; i<fs.size(); ++i) {
                    ifstream f;
                    f.open(fs[i], std::ifstream::in);
                    psr->q_stream(f);
                    stringstream c;
                    for(size_t j=name.size()+2; j<fs[i].size(); ++j) {
                        c.put(fs[i][j]);
                    }
                    t->append(psr->parse_thing(c.str()));
                }
                return t;
            }

            stringstream err;
            err << "Attempting to load un-cached variable \033[3m" << name << "\033[0m\n";
            err << " Not implemented!";
            throw runtime_error(err.str());
        }

        Thing *
        Store::retrieve( string const &name ) {
            if( data.count(name)==0 ) {
                Thing *v = lazy_load( name );
                data[name] = v;
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
            Thing *copy_parser = ((Parser*)parser)->clone();
            Store *s2 = new Store( root.prefix(), (Parser*)copy_parser );
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

        Thing *
        Store::invoke( string const &method, Thing *arg ) {
            (void)method; (void)arg;
            throw runtime_error("Not implemented.");
        }
    }
}