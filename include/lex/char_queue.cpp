#include "char_queue.hpp"

namespace rhizome {
    namespace lex {

        CharQueue::CharQueue() {

        }

        void
        CharQueue::dump( ostream &out ) const {
            out << "Character queue, front-to-back.\n\t\t";
            for(size_t i=0; i<chars.size(); ++i) {
                out << "'";
                out.put(chars[i]);
                out << "' ";
            }
            out << '\n';
        }

        void CharQueue::clear() {
            chars.clear();
        }

        void 
        CharQueue::put_back( wchar_t c ) {
            chars.push_front(c);
        }

        void 
        CharQueue::q( wchar_t c ) {
            chars.push_back(c);
        }

        bool 
        CharQueue::empty() const {
            return chars.size()==0;
        }
        
        wchar_t
        CharQueue::next() {
            if( empty() ) {
                throw runtime_error("Character queue is empty!");
            }
            wchar_t c = chars.front();
            chars.pop_front();
            return c;
        }

        string
        CharQueue::rhizome_type() const {
            return "Deque(Char)";
        }

        void
        CharQueue::serialize_to( size_t level, std::ostream &out ) const {
            (void)level;
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
        CharQueue::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method;(void)arg; (void)context;
            throw runtime_error("Nothing to invoke.");
        }
    }
}