#include "literal.hpp"

namespace rhizome {
    namespace parse {
        Literal::Literal( string const &w ): value(w) {
            
        }


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        void
        Literal::match( ILexer *lexer, GrammarFn lookup ) {
            Thing *temp = lexer->next_thing();
            stringstream v;
            temp->serialize_to(v);
            string token_value = v.str();
            if( token_value != value) {
                stringstream ss;
                ss << "Unmatched token: '" << token_value << "'  [Type is " << temp->rhizome_type() << "]\n";
                ss << "\tExpected literal '" << value << "'\n";
                delete temp;
                throw runtime_error(ss.str());
            }
            delete temp;
            append_all({new rhizome::types::String(token_value)});
        }

        bool
        Literal::can_match( ILexer *lexer, GrammarFn lookup ) const {
            if( !lexer->has_next_thing() ) return false;

            Thing *temp = lexer->peek_next_thing(0);
            stringstream v;
            temp->serialize_to(v);
            delete temp;
            bool r =  v.str()==value;
            return r;
        }

#pragma GCC diagnostic pop

        Gramex *
        Literal::clone_gramex() const {
            Literal *l = new Literal(value);
            return l;
        }

        void
        Literal::serialize_to( std::ostream &out ) const {
            out << "\"" << value << "\"";
        }


        string
        Literal::rhizome_type() const {
            return "gramex::Literal";
        }

        bool
        Literal::has_interface(string const &name ) {
            return name==rhizome_type()||name=="Gramex"||name=="Thing";
        }

    }
}