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

        l->define_token_type( name, new pat::Transform( hyphened_word, [](Thing *t){
            return t;
        } ));
    }

    /// Define a name token without hyphens
    void tt_word( string const &name, ILexer *l ) {
        IPattern *word = new pat::Plus(new pat::Alpha());
        l->define_token_type( name, new pat::Transform( word, [](Thing *t){
            return t;
        }));
    }

    /// Define a token type for a particular literal operator
    void tt_operator( string const &name, string const &op, ILexer *l ) {
        IPattern *opp = new pat::Literal(op);
        l->define_token_type( name, opp );
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
}