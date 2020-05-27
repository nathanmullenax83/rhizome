#include "whitespace.hpp"
#include "types/string.hpp"
#include "ui.hpp"

using rhizome::types::String;
namespace ui = rhizome::ui;

namespace rhizome {
    namespace pattern {
        Whitespace::Whitespace(): state(0) {

        }

        void
        Whitespace::reset() {
            state = 0;
            _valid = true;
            _captured = stringstream();
        }

        bool
        Whitespace::can_transition(char c) const {
            return _valid && state==0 && std::isspace(c);
        }

        void
        Whitespace::transition(char c) {
            if( can_transition(c)) {
                state = 1;
                _captured.put(c);
                return;
            } else {
                std::cout << "whitespace? '";
                std::cout.put(c);
                std::cout << "'\n";
                std::cout << "state = " <<state << "\n";
                throw runtime_error("Whitespace: invalid state transition");
            }
        }

        bool 
        Whitespace::accepted() const {
            return state==1;
        }

        IPattern *
        Whitespace::clone_pattern(bool withstate) const {
            Whitespace *ws = new Whitespace();
            if( withstate) {
                ws->_valid = _valid;
                ws->_captured << _captured.str();
                ws->state = state;
            }
            return ws;
        }

        Thing *
        Whitespace::captured_plain() {
            if( accepted() ) {
                Thing *s = new String(_captured.str());
                return s;
            } else {
                throw runtime_error("Whitespace: not in accept state!");
            }
        }

        Thing *
        Whitespace::captured_transformed(){
            return captured_plain();
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

        Thing *
        Whitespace::invoke( string const &method, Thing *arg ) {
            if( method=="clone" && arg==NULL ) return clone();
            throw runtime_error("Invalid invocation.");
        }

        

        bool
        Whitespace::verify( std::ostream &out ) {
            bool checked=true;
            

            checked = checked && assertion(out,
                can_transition(' '),
                "Whitespace pattern can_transition on space character."
            );
            checked = checked && assertion(out,
                can_transition('\t'),
                "Whitespace pattern can_transition on tab character."
            );
            checked = checked && assertion(out,
                can_transition('\n'),
                "Whitespace pattern can_transition on newline."
            );
            checked = checked && assertion(out,
                (transition(' '), accepted()),
                "Whitespace pattern accepts space."
            );
            checked = checked && assertion(out,
                _captured.str()==" ",
                "Whitespace pattern captures a space character."
            );
            reset();
            checked = checked && assertion(out,
                state==0,
                "Reset sets state to 0."
            );
            checked = checked && assertion (out,
                _captured.str().length()==0,
                "Reset clears captured string."
            );

            return checked;
        }
    }
}