#include "n_times.hpp"



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
            this->Pattern::reset();
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
                    IPattern *copy = inner->clone_pattern();
                    copy->reset();
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
                return;
            } else if( inner->accepted() ) {
                if( n < N-1 ) {
                    ++n;
                    inner->reset();
                    if( inner->can_transition(c)) {
                        inner->transition(c);
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
        NTimes::clone_pattern() const {
            NTimes *p = new NTimes(N,inner->clone_pattern());
            p->n = n;
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
    }
}