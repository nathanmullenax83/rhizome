#include "tuple.hpp"

using rhizome::core::Dispatcher;
using rhizome::core::indent;

namespace rhizome {
    namespace types {
        namespace tuples {
            static Dispatcher<Tuple> dispatcher({
                {
                    "evaluate",[](Thing *context, Tuple *that, Thing *arg) {
                        assert(arg==NULL);
                        return that->evaluate(context);
                    }
                },
                {
                    "append",[](Thing *context, Tuple *that, Thing *arg) {
                        (void)context;
                        assert(arg!=NULL);
                        that->append(arg);
                        return that;
                    }
                },
                {
                    "prepend",[](Thing *context, Tuple *that, Thing *arg) {
                        (void)context;
                        assert(arg!=NULL);
                        that->prepend(arg);
                        return that;
                    },
                }
            });
        }

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
                items[i]->serialize_to(0,e);
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
        Tuple::serialize_to( size_t level, ostream &out ) const {
            out << indent(level) << "(\n";
            for(size_t i=0; i<items.size();++i) {
                items[i]->serialize_to(level+1,out);
                if( i < items.size()-1) {
                    out << ",";
                }
            }
            out << indent(level) << ")\n";
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
            try {
                return tuples::dispatcher.at(method)(context,this,arg);
            } catch( std::exception *e ) {
                if( tuples::dispatcher.count(method)==0) {
                    throw runtime_error( rhizome::core::invoke_method_not_found(method,this,context));
                } else {
                    throw runtime_error( rhizome::core::invoke_error(method,arg,this,context,e));
                }
            }
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

        Thing *
        Tuple::evaluate( Thing *context ) const {
            (void)context;
            return clone();
        }

    }
}