#include <stdexcept>

#include "beginning.hpp"

using std::runtime_error;

namespace rhizome {
    namespace pattern {

        Beginning::Beginning(): state(0) {

        }

        void 
        Beginning::reset() {
            state = 0;
            this->Pattern::reset();
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
            return true;
        }
            
        IPattern * 
        Beginning::clone_pattern() const {
            Beginning *b = new Beginning();
            b->state = state;
            return b;
        }
        

        void
        Beginning::serialize_to( ostream &out ) const {
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
        Beginning::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}