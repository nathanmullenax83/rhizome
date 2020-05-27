#include "literal.hpp"

#include "log.hpp"

namespace rhizome {
    namespace parse {
        Literal::Literal( string const &w ): value(w) {
            
        }


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        void
        Literal::match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) {
            //static rhizome::log::Log log("literal_match");
            if( value != "" && !lexer->has_next_thing()) {
                stringstream err;
                err << "Cannot match literal '" << this->value << "' because there are no more tokens.";
                throw runtime_error(err.str());
            }
            string putback;
            Thing *temp = lexer->next_thing(putback);
            //log.info("Next thing (putback): ");
            //log.info(putback);
            //std::cout << "Value = " << putback << "\n";
            if( temp!=NULL ) {
               // std::cout << "Type = " << temp->rhizome_type() << "\n";
                stringstream v;
                temp->serialize_to(v);
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
            if( !lexer->has_next_thing() ) return false;

            Thing *temp = (lexer->peek_next_thing(1,true))[0];
            
            stringstream v;
            temp->serialize_to(v);
            delete temp;
            bool r =  v.str()==value;
            return r;
        }

#pragma GCC diagnostic pop

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

        Thing * Literal::invoke( string const &method, Thing *arg ) {
            (void)method; (void)arg;
            throw runtime_error("Nothing to invoke.");
        }

    }
}