#include <stdexcept>

#include "beginning.hpp"
#include "types/string.hpp"

using rhizome::types::String;

using std::runtime_error;

namespace rhizome {
    namespace pattern {

        Beginning::Beginning(): state(0) {

        }

        void 
        Beginning::reset() {
            state = 0;
            _valid = true;
            _captured = stringstream();
        }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

        bool 
        Beginning::can_transition(char c) const{
            return false;
        }
            
        void
        Beginning::transition(char c){
            invalidate();
            throw runtime_error("Couldn't match beginnning.");
        }

#pragma GCC diagnostic pop        
        bool 
        Beginning::accepted() const{
            return _valid && true;
        }
            
        IPattern * 
        Beginning::clone_pattern(bool withstate) const {
            Beginning *b = new Beginning();
            if(withstate){
                b->_valid = _valid;
                b->_captured << _captured.str(); // noop?
                b->state = state;
            }
            return b;
        }
        

        void
        Beginning::serialize_to( size_t level, ostream &out ) const {
            (void)level;
            out << "^";
        }

        string
        Beginning::rhizome_type() const {
            return "pattern::Beginning";
        }

        bool
        Beginning::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="Thing";
        }
        Thing *
        Beginning::invoke( Thing * context, string const &method, Thing *arg ) {
            (void)method;(void)arg;(void)context;
            throw runtime_error("Nothing to invoke.");
        }

        Thing *
        Beginning::captured_plain() {
            return new String("");
        }

        Thing *
        Beginning::captured_transformed() {
            return captured_plain();
        }
    }
}