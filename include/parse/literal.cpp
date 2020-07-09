#include "literal.hpp"

#include "log.hpp"

namespace rhizome {
    namespace parse {
        Literal::Literal( string const &w ): value(w) {
            
        }



        void
        Literal::match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) {
            (void)lookup; // don't need it here.

            // Throw error if there are no more tokens and we are trying to 
            // extract a non-empty /value/
            if( value != "" && !lexer->has_next_thing()) {
                stringstream err;
                err << "Cannot match literal '" << this->value << "' because there are no more tokens.";
                throw runtime_error(err.str());
            }

            // putback is to contain the literal extracted text (including whitespace)
            string putback;
            // get the next token and record it in putback if it is not a match
            Thing *temp = lexer->next_thing(putback);
            
            if( temp!=NULL ) {
                stringstream v;
                temp->serialize_to(0,v);
                string token_value = v.str();
                
                if( token_value != value) {
                    stringstream ss;
                    ss << "Unmatched token: '" << token_value << "'  [Type is " << temp->rhizome_type() << "]\n";
                    ss << "\tExpected literal '" << value << "'\n";
                    std::cerr << ss.str();
                    delete temp;
                    throw runtime_error(ss.str());
                }
                delete temp;
                captured << putback;
                append_all({new rhizome::types::String(token_value)});
            }

        }

        bool
        Literal::can_match( ILexer *lexer, GrammarFn lookup ) const {
            (void)lookup; //unneeded
            if( !lexer->has_next_thing() ) return false;

            Thing *temp = (lexer->peek_next_thing(1,true))[0];
            
            stringstream v;
            temp->serialize_to(0,v);
            delete temp;
            bool r =  v.str()==value;
            return r;
        }



        Gramex *
        Literal::clone_gramex(bool withmatches) const {
            Literal *l = new Literal(value);
            if( withmatches ) {
                l->append_all( clone_matched_tokens() );
            }
            return l;
        }

        bool
        Literal::accepts(GrammarFn lookup) const {
            (void)lookup;
            return value=="";
        }

        void
        Literal::serialize_to( size_t level, std::ostream &out ) const {
            (void)level;
            out << "\"" << value << "\"";
        }


        string
        Literal::rhizome_type() const {
            return "gramex::Literal";
        }

        bool
        Literal::has_interface(string const &name ) {
            return name==rhizome_type()||name=="gramex"||name=="Thing";
        }

        Thing * Literal::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method; (void)arg; (void)context;
            throw runtime_error("Nothing to invoke.");
        }

        

    }
}