#include "classifier.hpp"

namespace rhizome {
    namespace alphabet {

        Classifier::Classifier() {

        }

        Classifier::~Classifier() {
            
        }

        set< string >
        Classifier::classes( unsigned long long c ) const {
            set<string> cs;
            for( auto i=fns.begin(); i!=fns.end(); i++) {
                if( i->second.operator()(c)) {
                    cs.insert( i->first );
                }
            }
            return cs;
        }

        bool 
        Classifier::member( string const &name, unsigned long long c ) const {
            assert( fns.count(name) > 0 );
            auto f = fns.at(name);
            return f(c);
        }

        void Classifier::define_set( string const &name, function< bool(unsigned long long) > f) {
            fns[name] = f;
        }

        void Classifier::define_set( string const &name, string const &chars ) {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring ws = converter.from_bytes(chars);   
            set<unsigned long long> s;
            fns[name] = [s]( unsigned long long c ) { return s.count(c) > 0; };
        }

        void Classifier::define_range( string const &name, unsigned long long begin, unsigned long long end ) {
            fns[name] = [begin,end]( unsigned long long c ) {
                return (c >= begin) && (c <= end);
            };
        }

        void Classifier::define_union( string const &name, string const &first, string const &second ) {
            assert( !(name == first || name == second) );
            assert( fns.count(first) > 0 );
            assert( fns.count(second) > 0 );
            
            auto f0 = fns[first];
            auto f1 = fns[second];
            fns[name] = [f0,f1]( unsigned long long c ) {
                return f0(c)||f1(c);
            };
        }

        void Classifier::define_union( string const &name, vector<string> const &cs ) {
            vector< function< bool(unsigned long long) > > fs;
            for(size_t i=0; i<cs.size(); ++i) {
                string name = cs.at(i);
                assert( fns.count(name) > 0); // function exists
                fs.push_back( fns.at(name));
            }
            // capture function pointer table to construct union function
            fns[name] = [fs]( unsigned long long c ) {
                bool member = false;
                for(size_t i=0; i<fs.size(); ++i) {
                    member = member || fs[i](c);
                    if( member ) return true; // short circuit
                }
                return member;
            };
        }

        void Classifier::define_intersection( string const &name, string const &first, string const &second ) {
            assert( name != first );
            assert( name != second );
            assert( fns.count(first) > 0);
            assert( fns.count(second) > 0 );
            auto f0 = fns[first];
            auto f1 = fns[second];
            fns[name] = [f0,f1]( unsigned long long c ) {
                return f0(c)&&f1(c);
            };
        }

        void Classifier::define_intersection( string const &name, vector<string> const &cs ) {
            vector< function< bool(unsigned long long) > > fs;
            for(size_t i=0; i<cs.size(); ++i) {
                string name = cs.at(i);
                assert( fns.count(name) > 0); // function exists
                fs.push_back( fns.at(name));
            }
            // capture function pointer table to construct union function
            fns[name] = [fs]( unsigned long long c ) {
                bool member = true;
                for(size_t i=0; i<fs.size(); ++i) {
                    member = member && fs[i](c);
                    if( !member ) return false; // short circuit
                }
                return member;
            };
        }

        void Classifier::define_difference( string const &name, string const &first, string const &second ) {
            assert( name != first );
            assert( name != second );
            assert( fns.count(first) > 0 );
            assert( fns.count(second) > 0 );
            auto f0 = fns[first];
            auto f1 = fns[second];
            fns[name] = [f0,f1](unsigned long long c) {
                return f0(c) && (!f1(c));
            };
        }

        void Classifier::define_complement( string const &name, string const &s ) {
            assert( name != s );
            assert( fns.count(name) > 0 );
            auto f = fns[name];
            fns[name] = [f]( unsigned long long c ) {
                return !f(c);
            };
        }


        // thing implementation
        Thing * 
        Classifier::invoke( Thing *context, string const &method, Thing * arg ) {
            (void)context;
            if( method=="∪" || method=="|") {
                assert( arg!=NULL && arg->rhizome_type()=="Tuple" );
                Tuple *classes = (Tuple*)arg;
                Thing *nc = classes->extract_first();
                assert( nc!=NULL && nc->rhizome_type()=="String");
                String *name = (String*)nc;
                define_union( name->native_string(), classes->get_vector_of_native_strings());
                delete arg;
                return new Tuple();
            } else if( method=="∩" || method=="&") {
                assert( arg!=NULL && arg->rhizome_type()=="Tuple" );
                Tuple *classes = (Tuple*)arg;
                Thing *nc = classes->extract_first();
                assert( nc!=NULL && nc->rhizome_type()=="String");
                String *name = (String*)nc;
                define_intersection( name->native_string(), classes->get_vector_of_native_strings());
                delete arg;
                return new Tuple();
            } else if( method=="\\" || method=="-") {
                // A = B - C
                assert( arg!=NULL && arg->rhizome_type()=="Tuple");
                Tuple *targs = (Tuple*)arg;
                assert( targs->size()==3);
                vector<string> sargs = targs->get_vector_of_native_strings();
                define_difference( sargs[0], sargs[1], sargs[2]);
                delete arg;
                return new Tuple();
            } else if( method=="′") {
                assert( arg!=NULL && arg->rhizome_type()=="Tuple");
                vector<string> ps = ((Tuple*)arg)->get_vector_of_native_strings();
                assert( ps.size()==2);
                define_complement( ps[0], ps[1]);
                delete arg;
                return new Tuple();
            } else if( method=="‥" || method=="..") {
                assert( arg!=NULL && arg->rhizome_type()=="Tuple");
                Tuple *ps = (Tuple*)arg;
                assert( ps->size()==3);
                Thing *name = ps->at(0);    assert( name!=NULL && name->rhizome_type()=="String");
                Thing *begin = ps->at(1);   assert( begin!=NULL && begin->rhizome_type()=="Char");
                Thing *end = ps->at(2);     assert( end !=NULL && end->rhizome_type()=="Char");
                String *sname = (String*)name;
                Char *cbegin = (Char*)begin;
                Char *cend = (Char*)end;
                define_range( sname->native_string(), cbegin->v, cend->v );
                delete arg;
                return new Tuple();
            }

            stringstream err;
            err << "'" << method << "' is an unknown method of " << rhizome_type();
            throw runtime_error(err.str());
        }

        bool Classifier::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }

        Thing * Classifier::clone() const {
            Classifier *c = new Classifier();
            c->fns = fns;
            return c;
        }

        void Classifier::serialize_to( std::ostream &out ) const {
            out << rhizome_type() << "{}";
        }

        string Classifier::rhizome_type() const {
            return "Classifier(Char)";
        }


        Classifier * create_rhizome_classifier() {
            Classifier *c = new Classifier();
            c->define_set( "α", iswalpha );
            c->define_set( "Ⅹ", iswdigit );
            c->define_set( "#", iswxdigit);
            c->define_set( "🕱", iswcntrl);
            c->define_set( "␣", iswspace );
            c->define_set( "▉", iswgraph );
            c->define_set( "⎙", iswprint );
            c->define_set( ".", iswpunct );
            c->define_set( "↓", iswlower);
            c->define_set( "↑", iswupper);
            c->define_set( "↵", [](unsigned long long c) { return c=='\n'; });
            return c;
        }
    }
}