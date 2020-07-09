#include "token_queue.hpp"

namespace rhizome {
    namespace lex {

        TokenQueue::TokenQueue() {

        }

        TokenQueue::~TokenQueue() {
            for(size_t i=0; i<things.size(); ++i) {
                delete things[i];
            }
        }

        void TokenQueue::clear() {
            for(size_t i=0; i<things.size(); ++i){
                delete things[i];
            }
            things.clear();
        }

        bool
        TokenQueue::empty() const {
            return things.size()==0;
        }

        void
        TokenQueue::put_back( Thing *t ) {
            // these are ignored productions
            if( t==NULL ) return;

            things.push_front(t);
        }

        void
        TokenQueue::q( Thing *t ) {
            if( t==NULL ) return;
            things.push_back( t );
        }

        Thing *
        TokenQueue::next() {
            if( things.size() == 0 ) {
                throw runtime_error("No tokens available.");
            }
            Thing * t = things.front();
            things.pop_front();
            return t;
        }

        string
        TokenQueue::rhizome_type() const {
            return "Deque(Token)";
        }

        bool
        TokenQueue::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }

        void 
        TokenQueue::serialize_to( size_t level, std::ostream &out ) const {
            (void)level;
            out << rhizome_type() << "(";
            out << ")";
        }

        Thing *
        TokenQueue::clone() const {
            TokenQueue *copy = new TokenQueue();
            for(size_t i=0; i<things.size(); ++i) {
                copy->things.push_back( things[i]->clone() );
            }
            return copy;
        }
        
        Thing *
        TokenQueue::invoke( Thing *context, string const &op, Thing *arg ) {
            (void)context;
            if( op=="clone" ) {
                return clone();
            } else if( op=="has_interface" && arg->rhizome_type()=="String") {
                stringstream name;
                arg->serialize_to(0,name);
                return new Bool( has_interface(name.str()));
            } else if( op=="next" ) {
                return next();
            } else {
                throw runtime_error("No such method.");
            }
        }
    }
}