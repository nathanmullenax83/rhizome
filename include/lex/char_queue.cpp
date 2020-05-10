#include "char_queue.hpp"

namespace rhizome {
    namespace lex {

        CharQueue::CharQueue() {

        }

        void
        CharQueue::dump( ostream &out ) const {
            out << "Character queue, front-to-back.\n\t\t";
            for(size_t i=0; i<chars.size(); ++i) {
                out << ((char)chars[i]) << ' ';
            }
            out << '\n';
        }

        void 
        CharQueue::put_back( unsigned long long int c ) {
            chars.push_front(c);
        }

        void 
        CharQueue::q( unsigned long long int c ) {
            chars.push_back(c);
        }

        bool 
        CharQueue::empty() const {
            return chars.size()==0;
        }
        
        unsigned long long int 
        CharQueue::next() {
            if( empty() ) {
                throw runtime_error("Character queue is empty!");
            }
            unsigned long long int c = chars.front();
            chars.pop_front();
            return c;
        }

        string
        CharQueue::rhizome_type() const {
            return "Deque(Char)";
        }

        void
        CharQueue::serialize_to( std::ostream &out ) const {
            out << rhizome_type() << "(";
            out << ")";
        }

        bool
        CharQueue::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }

        Thing *
        CharQueue::clone() const {
            CharQueue *copy = new CharQueue(*this);
            return copy;
        }

        Thing *
        CharQueue::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}