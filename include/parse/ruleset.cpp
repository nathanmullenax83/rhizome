#include "ruleset.hpp"

namespace rhizome {
    namespace parse {
        Ruleset::Ruleset() {
            
        }

        Ruleset::~Ruleset() {
            for( auto i = rules.begin(); i!=rules.end(); ++i) {
                delete i->second.first;
            }
            
        }

        void Ruleset::rule( string const &w, Gramex *x, ParseFn f ) {
            pair< Gramex *, ParseFn > rec;
            rec.first = x;
            rec.second = f;

            if( rules.count(w) > 0 ) {
                rules[w] = rec;
            } else {
                delete rules[w].first;
                rules[w] = rec;
            }
        }

        Gramex *
        Ruleset::lookup( string const &name ) const {
            if( rules.count(name)) {
                return rules.at(name).first->clone_gramex();
            } else {
                throw runtime_error("Rule does not exist.");
            }

        }

        ParseFn
        Ruleset::lookup_parser( string const &name ) const {
            if( rules.count(name)) {
                return rules.at(name).second;
            } else {
                throw runtime_error("Parser does not exist.");
            }
        }
    }
}