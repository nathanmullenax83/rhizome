#include "match_type.hpp"

namespace rhizome {
    namespace parse {
        MatchType::MatchType( string const &tname ): name(tname) {

        }

        Gramex *
        MatchType::clone_gramex() const {
            MatchType *mt = new MatchType(name);
            return mt;
        }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        void
        MatchType::match( ILexer *lexer, GrammarFn lookup ) {
            Thing *temp = lexer->next_thing();
                
            if( temp->rhizome_type() != name ) {
                stringstream ss;
                ss << "Expected token of type " << name << ", but got " << temp->rhizome_type();
                delete temp;
                throw runtime_error(ss.str());
            } else {
                append_all({temp->clone()});
                delete temp;
            }
            

        }

        bool
        MatchType::can_match( ILexer *lexer, GrammarFn lookup ) const {
            if( lexer->has_next_thing()) {
                Thing *p = lexer->peek_next_thing(0);
                return p->rhizome_type()==name;
            } else {
                return false;
            }
        }
#pragma GCC diagnostic pop


        void
        MatchType::serialize_to( std::ostream &out ) const {
            out << "<" << name << ">";
        }

        string
        MatchType::rhizome_type() const {
            return "gramex::MatchType";
        }

        bool
        MatchType::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Gramex"||name=="Thing";
        }
    }
}