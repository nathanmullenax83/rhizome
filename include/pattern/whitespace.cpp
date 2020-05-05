#include "whitespace.hpp"

namespace rhizome {
    namespace pattern {
        Whitespace::Whitespace(): state(0) {

        }

        void
        Whitespace::reset() {
            state = 0;
            this->Pattern::reset();
        }

        bool
        Whitespace::can_transition(char c) const {
            return state==0 && std::isspace(c);
        }

        void
        Whitespace::transition(char c) {
            if( can_transition(c)) {
                state = 1;
                return;
            } else {
                throw runtime_error("Whitespace: invalid state transition");
            }
        }

        bool 
        Whitespace::accepted() const {
            return state==1;
        }

        IPattern *
        Whitespace::clone_pattern() const {
            Whitespace *ws = new Whitespace();
            ws->state = state;
            return ws;
        }

        void 
        Whitespace::serialize_to_cclass_context( ostream &out ) const {
            out << ":space:";
        }

        void 
        Whitespace::serialize_to( ostream &out ) const {
            out << "[";
            serialize_to_cclass_context(out);
            out << "]";
        }

        string
        Whitespace::rhizome_type() const {
            return "pattern::Whitespace";
        }

        bool
        Whitespace::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="Class(Char)"||name=="Thing";
        }
    }
}