#include "rhizome.hpp"

#include <fstream>

using std::ifstream;

using rhizome::parse::Parser;
using namespace rhizome::parse;
namespace pat = rhizome::pattern;
namespace tps = rhizome::types;
namespace rhizome{
    /// Define a token-type that matches hyphenated words and returns it as a String.
    void tt_hyphened_word( string const &name, ILexer *l) {
        IPattern *word = new pat::Plus(new pat::Alpha());
        pat::Cat *hyphened_word = new pat::Cat(word, new pat::Literal("-"));
        hyphened_word->append((Pattern*)word->clone_pattern(false));
        l->define_token_type( name, hyphened_word );
    }

    /// Define a name token without hyphens
    void tt_word( string const &name, ILexer *l ) {
        IPattern *word = new pat::Plus(new pat::Alpha());
        l->define_token_type( name, word );
    }

    /// Define a token type for a particular literal operator
    void tt_operator( string const &name, string const &op, ILexer *l ) {
        IPattern *opp = new pat::Literal(op);
        l->define_token_type( name, opp );
    }

    IParser * create_rhizome_parser() {
        Parser *parser = new Parser();
        return parser;
    }    

    /// Define a token-type that is an ALLCAPS

    IParser *create_lexer_grammar() {
        Parser *p = new Parser();
        
        
        tt_hyphened_word( "A_HYPHENED_WORD", p->get_lexer());
        tt_word( "A_WORD", p->get_lexer());
        tt_operator( "A_PASCAL_RANGE_OPERATOR", "..", p->get_lexer());

        p->get_lexer()->define_token_type("A_YELLED", 
            new rhizome::pattern::Transform( 
                new rhizome::pattern::Group( new rhizome::pattern::Plus( new rhizome::pattern::Range('A','Z')) ),
                [](Thing * t){
                    std::cout << "A_YELLED: ";
                    t->serialize_to(std::cout);
                    std::cout << "\n";
                    return t;
                }));
        p->get_lexer()->define_token_type("A_USASCII", new pat::Transform( new rhizome::pattern::Literal("US-ASCII"),[](Thing *t){
            return t;
        }));
        p->get_lexer()->define_token_type("A_8BIT", new pat::Transform( new rhizome::pattern::Literal("8-bit"),[]( Thing *t) {
            return t;
        }));
        p->rule("LexerDefinition", 
            apply(plus(seq(non_term("Rule"),match_lexer_rule("Newline"))), []( deque<Thing*> ts ) {
                Lexer *l = new Lexer();
                for( size_t i=0; i<ts.size(); i+=2) {
                    tps::Tuple *rule = (tps::Tuple*)ts[i];
                    tps::String *name = (tps::String*)rule->at(0);
                    Pattern *pat = (Pattern*)rule->at(1);
                    l->define_token_type( name->native_string(), new pat::Transform( pat, []( Thing *t ){
                        return t;
                    }));
                    delete name;
                }
                return (Thing*)l;
            })
        );
        p->rule( "Rule", apply(seq({
            match_lexer_rule("A_YELLED"),
            lit("="), lit("<"), non_term("Definition"), lit(">")
        }), []( deque<Thing*> ts){
            std::cout << "Rule: ";
            ts[0]->serialize_to(std::cout);
            tps::Tuple *vs = new tps::Tuple();
            vs->append( ts[0]); // name of token type
            vs->append( ts[3]); // non-term "Definition"
            vs->serialize_to(std::cout);
            return vs;
        } ));
        p->rule("Definition", options({
            seq(lit("any"), non_term("DefinitionAny")),
            seq(lit("US-ASCII"), non_term("DefinitionASCII"))
        }));
        p->rule("DefinitionAny", options({
            seq(lit("8-bit"), non_term("SequenceOfData")),
            seq(lit("US-ASCII"), non_term("ASCIISubset"))
        }));
        p->rule("SequenceOfData", seq(lit("sequence"),lit("of"), lit("data")));
        p->rule("DefinitionASCII", options({
            seq(match_lexer_rule("A_YELLED"), lit(","), non_term("EntityNameAndDefinition")),
            non_term("EntityNameAndDefinition")
        }));
        p->rule("EntityNameAndDefinition", 
            seq(
                non_term("EntityName"),
                non_term("EntityDefinition"))
            );
        p->rule("EntityName",
            plus( options({ match_lexer_rule("A_WORD"), match_lexer_rule("A_HYPHENED_WORD")}))
        );
        p->rule("EntityDefinition",
            seq( lit("("), match_type("Integer"), lit(")"))
        );
        p->rule("ASCIISubset", 
            seq(non_term("EntityName"), non_term("CharacterRange"))
        );
        p->rule("CharacterRange",
            options({
                seq(lit("("), maybe(lit("octets")), non_term("HyphenRange"), lit(")")),
                seq(match_lexer_rule("String"), lit(".."), match_lexer_rule("String"))
            })
        );
        p->rule("HyphenRange",
            seq(match_type("Integer"), lit("-"), match_type("Integer"))
        );
        return p;
    }

    ILexer *load_lexer( string const &fn ) {
        ifstream f;
        f.open( fn, ifstream::in );
        IParser *p = create_lexer_grammar();
        std::cout << "Created grammar for lexer definition.\n";
        assert(p!=NULL);
        p->q_stream(f);
        std::cout << "Queued file contents: lexer/http.lexer.\nParsing...\n";
        try {
            return (Lexer*)p->parse_thing( "LexerDefinition");
        } catch( std::exception *e ) {
            std::cout << e->what();
        }
        throw runtime_error("Failed to load lexer.");
    }

    bool verify() {
        bool checked = true;
        {
            rhizome::pattern::Whitespace ws; 
            checked = checked && ws.verify(std::cout);
        }
        return checked;
    }

    bool system_bool( Thing *t ) {
        if( t!=NULL && t->rhizome_type()=="Bool") {
            Bool *b = (Bool*)t;
            return b->value;
        } else {
            throw runtime_error("Expected Bool value e.g., true, false, undetermined ;)");
        }
    }

    string to_system_string( Thing * t ) {
        if( t!=NULL ) {
            if( t->rhizome_type()=="String") {
                String *str = (String*)t;
                return str->native_string();
            } else {
                stringstream s;
                t->serialize_to(s);
                return s.str();
            }
        } else {
            return "";
        }
    }

    string t_not_expected( Thing *t, string const &expectation ) {
        stringstream s;
        s << expectation;
        t->serialize_to(s);
        return s.str();
    }

    mpz_class system_mpz( Thing *t ) {
        if( t!=NULL ) {
            if( t->rhizome_type()=="Int" ) {
                return ((Integer*)t)->value;
            } else {
                throw runtime_error(t_not_expected(t,"Expected Int, but got: "));
            }
        } else {
            throw runtime_error(t_not_expected(NULL, "Null might be said to correspond to zero. Not here, tho."));
        }
    }

    Thing * left_cdr( Tuple *t ) {
        if( t!=NULL && (t->size() > 0) ) {
            Thing * first = t->extract_first();
            return first;
        } else {
            throw runtime_error("Cannot extract first element of // customizean empty list.");
        }
    }

    Thing * right_cdr( Tuple *t ) {
        if( t!=NULL && (t->size() > 0)) {
            Thing *last = t->extract_last();
            return last;
        } else {
            throw runtime_error("Cannot extract last element of an empty list.");
        }
    }

    long double system_float( Thing *t ) {
        if( t!=NULL ) {
            if( t->rhizome_type()=="Float") {
                return ((tps::Float*)t)->value;
            } else if( t->rhizome_type()=="Fraction") {
                return ((tps::Fraction*)t)->decimal();
            } else if( t->rhizome_type()=="Integer") {
                return ((tps::Integer*)t)->native_int();
            }
            throw runtime_error(t_not_expected(t,"Expected a numeric value but got "));
        } else {
            throw runtime_error(t_not_expected(NULL, "Cannot extract float value from a NULL pointer."));
        }
    }

    
    string apply_mapping( string s, rhizome::alphabet::Mapping &m) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;   
        wstring w = converter.from_bytes(s);
        for(size_t i=0; i<w.length();++i) {
            wchar_t c = w.at(i);
            w[i] = m.lookup(c);
        }
        return converter.to_bytes(w);
    }


}