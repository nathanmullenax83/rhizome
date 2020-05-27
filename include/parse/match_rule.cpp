#include "match_rule.hpp"

namespace rhizome {
    namespace parse {
        MatchRule::MatchRule( string const &name ): name(name) {

        }

        bool 
        MatchRule::can_match( ILexer *lexer, GrammarFn lookup ) const {
            (void)lookup; // don't need it.
            // This is ultimately a statement about strings. The next 
            // lexical token can be accepted by the pattern currently
            // represented by /name/.
            // Use lexer to look up lexical rule named /name/
            IPattern *pattern = lexer->clone_pattern(name);
            Thing *nt = (lexer->peek_next_thing(1,true))[0];
            stringstream ss;
            nt->serialize_to(ss);
            bool cm = pattern->accepts(ss.str());
            delete nt; delete pattern;
            return cm;
        }

        void 
        MatchRule::match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) {
            (void)lookup;
            string putback;
            IPattern *pattern = lexer->clone_pattern(name);
            if( lexer->has_next_thing()) {
                Thing *nt = (lexer->peek_next_thing(1,false))[0];
                // make sure the pattern matches
                if( nt->rhizome_type() != "String") {
                    std::cout << "Token is not a string! " << nt->rhizome_type() << "\n";
                    nt->serialize_to(std::cout);
                    
                    throw runtime_error("Could not match rule.");
                }
                string tok = ((String*)nt)->native_string();
                if( !pattern->accepts( tok ) ) {
                    stringstream err;
                    err << "Error matching lexical rule. Token Pattern '" << name << "' cannot produce '" << tok << "'";
                    throw runtime_error(err.str());
                }
                // everything worked, free up token, pattern, and leave.
                append_all({nt}); // passing nt, which is a copy of an as-yet-to-be-removed token
                
                delete lexer->next_thing(putback); // this looks bad, but the token has already been copied.
                captured << putback;
            } else {
                // pattern might accept without matching anything (*, for instance)
                if( !pattern->accepted() ) {
                    stringstream err;
                    err << "Error matching rule '" << name << "': pattern cannot trivially accept, and there are no tokens to be had.\n";
                    throw runtime_error(err.str());
                }
                // Rule matched /nothing/, so there is nothing to be appended.
            }
            delete pattern;
            return;   
        }

        Gramex * 
        MatchRule::clone_gramex(bool withmatches) const {
            MatchRule *m = new MatchRule(name);
            if( withmatches ) {
                m->append_all( clone_matched_tokens());
            }
            return m;
        }

        void MatchRule::serialize_to( std::ostream &out ) const {
            out << "<" << name << ">";
        }


        string MatchRule::rhizome_type() const {
            return "gramex::MatchRule";
        }

        bool MatchRule::has_interface( string const &name ) {
            return name==rhizome_type()||name=="gramex"||name=="Thing";
        }
        
        Thing * MatchRule::invoke( string const &method, Thing *arg ) {
            if( method=="clone" && arg==NULL ) {
                return clone_gramex(true);
            }
            throw runtime_error("Not implemented.");
        }

        bool MatchRule::accepts(GrammarFn lookup) const {
            (void)lookup;
            return match_count() > 0;
        }
    }
}