#include "ruleset.hpp"

using rhizome::core::Dispatcher;

namespace rhizome {
    namespace parse {
        namespace ruleset {
            static Dispatcher<Ruleset> dispatcher ({

            });
        }

        Ruleset::Ruleset() {
            
        }

        Ruleset::~Ruleset() {
            for( auto i = rules.begin(); i!=rules.end(); ++i) {
                delete i->second;
            }
            
        }

        void
        Ruleset::dump(std::ostream &out) const {
            out << "Parser rules:\n";
            for( auto i=rules.begin(); i!=rules.end(); i++) {
                out << "  ";
                out << i->first << " → ";
                i->second->serialize_to(0,out);
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

        string
        Ruleset::rhizome_type() const {
            return "parse.Ruleset";
        }

        bool
        Ruleset::has_interface( string const &name ) {
            return name=="Thing"||name==rhizome_type();
        }

        void
        Ruleset::serialize_to(size_t level, std::ostream &out ) const {
            out << rhizome_type() << "{\n";
            for(auto i=rules.begin(); i!=rules.end(); i++) {
                out << "    " << i->first << ": ";
                i->second->serialize_to(level+1, out);
                out << "\n";
            }
            out << "}\n";
        }

        Thing *
        Ruleset::clone() const {
            Ruleset *copy = new Ruleset();
            for(auto i=rules.begin(); i!=rules.end(); i++) {
                copy->rules[i->first] =  i->second->clone_gramex(false);
            }
            return copy;
        }
        

        Thing *
        Ruleset::invoke( Thing *context, string const &method, Thing *arg ) {
            try {
                return ruleset::dispatcher.at(method)(context,this,arg);
            } catch( std::exception *e ) {
                if( ruleset::dispatcher.count(method)==0) {
                    throw runtime_error(rhizome::core::invoke_method_not_found(method,this,context));
                } else {
                    throw runtime_error(rhizome::core::invoke_error(method,arg,this,context,e));
                }
            }
        }

    }
}