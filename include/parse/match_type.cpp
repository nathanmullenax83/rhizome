#include "match_type.hpp"

#include "log.hpp"

namespace rhizome {
    namespace parse {
        MatchType::MatchType( string const &tname ): name(tname) {

        }

        Gramex *
        MatchType::clone_gramex(bool withmatches) const {
            MatchType *mt = new MatchType(name);
            if( withmatches ) {
                mt->append_all( clone_matched_tokens());
            }
            return mt;
        }

        bool
        MatchType::accepts(GrammarFn lookup) const {
            (void)lookup;
            return false;
        }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        void
        MatchType::match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) {
            //static rhizome::log::Log log("type_match");

            try {
                string putback;
//                log.info("Extracting next thing:");
                Thing *temp = lexer->next_thing(putback);
                //log.info("Putback buffer: ");
                //log.info(putback);
                if( temp->rhizome_type() != this->name ) {
                    stringstream ss;
                    ss << "Expected token of type " << name << ", but got " << temp->rhizome_type() <<" '";
                    temp->serialize_to(ss);
                    ss << "'";
                    
                    delete temp;
                    throw runtime_error(ss.str());
                } else {
                    append_all({temp});
                    captured << putback;
                }
            } catch( std::exception *e ) {
                std::cout << "Error: " << e->what() << "\n";
                dump(std::cout);

            }
#ifdef INSTRUMENTED
            std::cout << "-- /match type\n";
#endif
        }

        bool
        MatchType::can_match( ILexer *lexer, GrammarFn lookup ) const {
            if( lexer->has_next_thing()) {
                Thing *p = (lexer->peek_next_thing(1,true))[0];
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

        Thing *
        MatchType::invoke( Thing *context, string const &method, Thing *arg) {
            (void)method; (void)arg; (void)context;
            throw runtime_error("Invoke not implemented.");
        }

        void
        MatchType::dump( std::ostream &out ) const {
            out << "DEBUG DUMP: gramex::MatchType\n";
            out << "=============================\n";
            out << "\t" << "Type name: " << name;
            out << "====== END: gramex::MatchType\n";
        }
    }
}