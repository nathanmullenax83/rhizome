#include "n_times.hpp"

#include "types/string.hpp"

using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        NTimes::NTimes(size_t N, IPattern *inner): N(N), n(0), inner(inner) {

        }

        NTimes::~NTimes() {

        }

        void
        NTimes::reset() {
            n=0;
            inner->reset();
            _valid = true;
            _captured = stringstream();
            xd = stringstream();
        }

        bool
        NTimes::can_transition(char c) const {
            if( inner->can_transition(c)) {
#ifdef INSTRUMENTED
                std::cout << "Can accept '" << c << "'" << std::endl;
#endif
                return true;
            } else if ( inner->accepted() ) {
                if( n < N-1 ) {

                    IPattern *copy = inner->clone_pattern(false);
                    bool a = copy->can_transition(c);
                    delete copy;
#ifdef INSTRUMENTED
                    std::cout << (a?"Can":"Cannot") << " reset and transition on '" << c << "'" << std::endl;
#endif
                    return a;
                } else {
#ifdef INSTRUMENTED
                    std::cout << "No transitions available for '" << c << "'" << std::endl;
#endif
                    return false;
                }
            } else {
                return false;
            }
        }

        void
        NTimes::transition(char c) {
            if( inner->can_transition(c) ) {
                inner->transition(c);
                _captured.put(c);
                return;
            } else if( inner->accepted() ) {
                if( n < N-1 ) {
                    ++n;
                    // hairy
                    xd << ((String*)inner->captured_transformed())->native_string();
                    inner->reset();
                    if( inner->can_transition(c)) {
                        inner->transition(c);
                        _captured.put(c);
                        return;
                    }
                } 
            }
            throw runtime_error("No transition available.");
        }
        
        bool
        NTimes::accepted() const {
            return n==N-1 && inner->accepted();
        }

        IPattern *
        NTimes::clone_pattern(bool withstate) const {
            NTimes *p = new NTimes(N,inner->clone_pattern(withstate));
            if( withstate ) {
                p->n = n;
                p->_valid = _valid;
                p->_captured << _captured.str();
                p->xd << xd.str();
            }
            return p;
        }

        void
        NTimes::serialize_to( ostream &out ) const {
            ((Thing*)inner)->serialize_to(out);
            out << "{" << N << "}";
        }

        string
        NTimes::rhizome_type() const {
            return "pattern::NTimes";
        }

        bool
        NTimes::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="Closure"||name=="Thing";
        }

        Thing *
        NTimes::invoke( string const &method, Thing *arg ) {
            (void)method; (void)arg;
            throw runtime_error("Invalid invocation.");
        }

        Thing *
        NTimes::captured_plain()  {
            return new String(_captured.str());
        }

        Thing *
        NTimes::captured_transformed() {
            if( inner->accepted() ) {
                Thing *t = inner->captured_transformed();
                t->serialize_to(xd);
            }
            return new String(xd.str());
        }
    }
}