#include "gramex.hpp"

namespace rhizome {
    namespace parse {
        Gramex::~Gramex() {

        }

        void
        Gramex::append_all( deque<Thing *> ts ) {
            for( size_t i=0; i<ts.size(); ++i) {
                matched_tokens.push_back(ts[i]);
            }
        }

        void
        Gramex::clear() {
            // delete matches
            for(size_t i=0; i<matched_tokens.size(); ++i) {
                delete matched_tokens[i];
                matched_tokens[i] = NULL;
            }
            matched_tokens.clear();
        }

        // deque<Thing*>
        // Gramex::get_matched_tokens() {
        //     return matched_tokens;
        // }

        deque<Thing*>
        Gramex::clone_matched_tokens() const {
            deque<Thing*> copy;
            for(size_t i=0; i<matched_tokens.size(); ++i) {
                copy.push_back( matched_tokens[i]->clone() );
            }
            return copy;
        }

        Thing *
        Gramex::clone() const {
            return (Thing*)clone_gramex();
        }

        size_t
        Gramex::match_count() const {
            return matched_tokens.size();
        }
    }
}