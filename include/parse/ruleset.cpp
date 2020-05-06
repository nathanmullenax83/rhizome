#include "ruleset.hpp"

namespace rhizome {
    namespace parse {
        Ruleset::Ruleset() {
            
        }

        Ruleset::~Ruleset() {
            for( auto i = rules.begin(); i!=rules.end(); ++i) {
                delete i->second;
            }
            
        }

        void Ruleset::rule( string const &w, Gramex *x) {
            if( rules.count(w) > 0 ) {
                rules[w] = x;
            } else {
                delete rules[w];
                rules[w] = x;
            }
        }

        Gramex *
        Ruleset::lookup( string const &name ) const {
            if( rules.count(name)) {
                return rules.at(name)->clone_gramex();
            } else {
                throw runtime_error("Rule does not exist.");
            }

        }

        
    }
}