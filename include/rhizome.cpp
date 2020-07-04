#include "rhizome.hpp"

#include <fstream>

using std::ifstream;

using rhizome::parse::Parser;
using namespace rhizome::parse;
namespace pat = rhizome::pattern;
namespace tps = rhizome::types;

namespace Core = rhizome::core;
namespace Store = rhizome::store;



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
    /// OK, so this is an implicit grammar built around something
    /// in the HTTP header documentation describing the tokens used to 
    /// define HTTP headers within the document. The idea is, I can build a special
    /// purpose parser for other parts of the same document to semi-automate
    /// the process of writing a general HTTP parser.
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
        })); // end lexer rule.

        p->get_lexer()->define_token_type("A_8BIT", new pat::Transform( new rhizome::pattern::Literal("8-bit"),[]( Thing *t) {
            return t;
        })); // end lexer rule.

        p->rule("LexerDefinition", 
            gx_apply(
                gx_plus_closure(
                    gx_sequence({
                        gx_non_terminal("Rule"),
                        gx_match_lexer_rule("Newline")
                    })
                ), 
                []( deque<Thing*> ts ) {
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
                }
            )
        ); // end rule

        p->rule( "Rule", 
            gx_apply(
                gx_sequence({
                    gx_match_lexer_rule("A_YELLED"),
                    gx_literal("="), 
                    gx_literal("<"), 
                    gx_non_terminal("Definition"), 
                    gx_literal(">")
                }), 
                []( deque<Thing*> ts){
                    std::cout << "Rule: ";
                    ts[0]->serialize_to(std::cout);
                    tps::Tuple *vs = new tps::Tuple();
                    vs->append( ts[0]); // name of token type
                    vs->append( ts[3]); // non-term "Definition"
                    vs->serialize_to(std::cout);
                    return vs;
                } // end parse-time application
            ) // end apply
        ); // end rule

        p->rule("Definition", gx_options({
            gx_sequence({gx_literal("any"), gx_non_terminal("DefinitionAny")}),
            gx_sequence({gx_literal("US-ASCII"), gx_non_terminal("DefinitionASCII")})
        }));
        p->rule("DefinitionAny", gx_options({
            gx_sequence({gx_literal("8-bit"), gx_non_terminal("SequenceOfData")}),
            gx_sequence({gx_literal("US-ASCII"), gx_non_terminal("ASCIISubset")})
        }));

        p->rule("SequenceOfData", 
            gx_sequence({
                gx_literal("sequence"),
                gx_literal("of"), 
                gx_literal("data")
            })
        ); // end rule

        p->rule("DefinitionASCII", 
            gx_options({
                gx_sequence({
                    gx_match_lexer_rule("A_YELLED"), 
                    gx_literal(","), 
                    gx_non_terminal("EntityNameAndDefinition")
                }
            ),
            gx_non_terminal("EntityNameAndDefinition")
        }));

        p->rule("EntityNameAndDefinition", 
            gx_sequence({
                gx_non_terminal("EntityName"),
                gx_non_terminal("EntityDefinition")
            })
        ); // end of bridge rule

        p->rule("EntityName",
            gx_plus_closure( 
                gx_options({ 
                    gx_match_lexer_rule("A_WORD"), 
                    gx_match_lexer_rule("A_HYPHENED_WORD")
                })
            )
        ); // end entity-name rule.

        // entity definition
        p->rule("EntityDefinition",
            gx_sequence({
                gx_literal("("), 
                gx_match_type("Integer"), 
                gx_literal(")")
            })
        ); // entity is a specific character, represented by /Integer/ in ASCII

        p->rule("ASCIISubset", 
            gx_sequence({
                gx_non_terminal("EntityName"), 
                gx_non_terminal("CharacterRange")
            })
        ); // entityName refers to a subset of ASCII characters (a range).

        p->rule("CharacterRange",
            gx_options({
                gx_sequence({
                    gx_literal("("), 
                    gx_maybe(gx_literal("octets")), 
                    gx_non_terminal("HyphenRange"), 
                    gx_literal(")")
                }), // range specified using a hyphen '-'
                gx_sequence({
                    gx_match_lexer_rule("String"), 
                    gx_literal(".."), 
                    gx_match_lexer_rule("String")
                }) // range specified using a Pascal-style range '..'
            })
        ); // end of character range rule.

        p->rule("HyphenRange",
            gx_sequence({
                gx_match_type("Int"), 
                gx_literal("-"), 
                gx_match_type("Int")
            })
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
            throw runtime_error("Cannot extract first element of an empty list.");
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


    void define_integer_expression( Parser * parser ) {
        parser->rule(
            "IntExpression",
            gx_sequence({
                gx_non_terminal("IntTerm"),
                gx_star_closure(
                    gx_sequence({
                        gx_options({
                            gx_literal("+"),
                            gx_literal("-")
                        }),
                        gx_non_terminal("IntTerm")
                    })
                )
            }));
        parser->rule(
            "IntTerm",
            gx_sequence({
                gx_non_terminal("IntLiteral"),
                gx_star_closure(
                    gx_sequence({
                        gx_options({
                            gx_literal("*"),
                            gx_literal("/")
                        }),
                        gx_non_terminal("IntLiteral")
                    })
                )
            })
        );
    }

    

    Core::System *
    plant(string const &docroot) {
        // Create a parser using the default lexer.
        Parser *parser = new Parser();
        Core::System *s = new Core::System(parser, new Store::Store(docroot, parser));

        define_integer_expression(parser);

        // The default lexer recognizes all of these types in literal form.
        // This code establishes a parser rule for each of the types.
        s->register_type("Bool",[s](Thing *t){
            return t;
        },[](IParser *p){
            Parser *parser = (Parser*)p;
            parser->rule("BoolLiteral",gx_match_lexer_rule("Bool"));
        });

        s->register_type("Int",[s](Thing *t){
            return t;   
        },[](IParser *p) {
            Parser *parser = (Parser*)p;
            parser->rule("IntLiteral",gx_match_lexer_rule("Int"));
        });

        s->register_type("String",[s](Thing *t){
            return t;
        },[](IParser *p){
            Parser *parser = (Parser*)p;
            parser->rule("StringLiteral",gx_match_lexer_rule("String"));
        });

        s->register_type("Decimal",[s](Thing *t){
            return t; 
        },[](IParser *p){
            Parser *parser = (Parser*)p;
            parser->rule("DecimalLiteral",gx_match_lexer_rule("Decimal"));
        });



        parser->rule( "Start", gx_options({
            gx_non_terminal("BoolLiteral"),
            gx_non_terminal("IntExpression"),
            gx_non_terminal("StringLiteral"),
            gx_non_terminal("DecimalLiteral")
        }));
        
        return s;
    }


}