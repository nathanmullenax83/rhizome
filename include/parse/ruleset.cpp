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

        void
        Ruleset::dump(std::ostream &out) const {
            for( auto i=rules.begin(); i!=rules.end(); i++) {
                out << "  ";
                out << i->first << " → ";
                i->second->serialize_to(out);
                out << "\n";
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
            if( rules.count(name) > 0) {
                return rules.at(name)->clone_gramex(false);
            } else {
                stringstream err;
                err << "Rule '" << name << "' does not exist in ruleset!\n";
                dump(err);
                throw runtime_error(err.str());
            }

        }

        
    }
}