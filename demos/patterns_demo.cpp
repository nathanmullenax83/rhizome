#include "patterns_demo.hpp"
#include "pattern.hpp"
#include "ui.hpp"

#include <functional>

using std::function;
using rhizome::pattern::Pattern;
using rhizome::ui::Console;

namespace rhizome {
    namespace demo {

        Pattern * whitespace_plus() {
            rp::Whitespace *ws = new rp::Whitespace();
            
            rp::Plus *p = new rp::Plus(ws);
            return p;
        }

        Pattern * literal( string const &w ) {
            rp::Literal *p = new rp::Literal(w);
            return p;
        }

        string exactly(size_t n, string const &w, bool quoted=false ) {
            stringstream ss;
            if( quoted ) { ss << "'"; n=n-2; }
            for(size_t i=0; i<n; ++i) {
                if( i < w.size() ) {
                    ss << w[i];
                } else if( i==w.size() && quoted ) {
                    ss << "'";
                } else {
                    ss << ' ';
                }
            }
            return ss.str();
        }


        string test_title( string testname, Pattern *p) {
            stringstream s;
            s << rhizome::ui::FG_YELLOW_ON;
            s << testname;
            s << rhizome::ui::RESET_COLOR;
            s << " : " << rhizome::ui::FG_CYAN_ON;
            p->serialize_to(s);
            s << rhizome::ui::RESET_COLOR;
            s << "\n";
            return s.str();

        }

        typedef function<bool(Console &)> Test;

        bool tr(Pattern * p, string const &s, bool expected ) {
            
            
            bool a = p->accepts(s);
            string pass(rl::green("🗹"));
            string fail(rl::red("𐄂"));
            stringstream color_s;
            color_s << "\033[1m";
            color_s << s;
            color_s << rhizome::ui::RESET_COLOR;
            std::cout << (a==expected ? pass : fail );
            std::cout << "  ";
            std::cout << exactly(30,color_s.str(),true) ;
            
            if( a ) {
                Thing * plain_capture = p->captured_plain();
                Thing * xd_capture = p->captured_transformed();

                stringstream buffer;
                buffer << rhizome::ui::BG_BLUE_ON;
                plain_capture->serialize_to(buffer);
                buffer << rhizome::ui::RESET_COLOR;
                std::cout << "  " << exactly(30,buffer.str());
                buffer = stringstream();
                
                if( xd_capture != NULL ) {
                    buffer << rhizome::ui::BG_MAGENTA_ON;
                    xd_capture->serialize_to(buffer);
                } else {
                    buffer << rhizome::ui::FG_GREEN_ON;
                    buffer << "NULL";
                }

                buffer << rhizome::ui::RESET_COLOR;
                std::cout << exactly(30,buffer.str());
                
            } 
            std::cout << "\n";
            return a==expected;
        }

        bool test_whitespace(Console &console) {
            rp::Pattern *p = whitespace_plus();
            console << test_title( "Whitespace pattern", p);
            bool status  = tr(p, " ",   true);
                
                 status &= tr(p, "  ",  true);
                 status &= tr(p, " a ", false);
                 status &= tr(p, "",    false);
            console << "\n";
            delete p;
            return status;
        }

        bool test_literal(Console &console) {
            rp::Pattern *p = literal("test");
            console << test_title( "Literal test", p);
            bool status  = tr(p, "test",           true);
                 status &= tr(p, "test testing",   false);
                 status &= tr(p, "  test",         false);
                 status &= tr(p, "test   tes",     false);
            console << "\n";
            delete p;
            return status;
        }

        bool test_or(Console &console) {
            rp::Or *p = new rp::Or();
            p->add_clause(literal("A"));
            p->add_clause(literal("B"));
            console << test_title( "Test or", p );
            bool status  = tr(p,"C",     false);
                 status &= tr(p,"B",     true);
                 status &= tr(p,"C",    false);
                 status &= tr(p,"A",      true);
            console << "\n";
            delete p;
            return status;
        }

        bool test_star(Console &console) {
            rp::Pattern *star = new rp::Star(literal("a"));
            console << test_title("Repetition", star);
            bool status  = tr(star,"",     true);
                 status &= tr(star,"a",    true);
                 status &= tr(star,"aa",   true);
                 status &= tr(star,"aaa",  true);
                 status &= tr(star,"aaba", false);
                 status &= tr(star,"aaaa", true);
            console << "\n";
            delete star;
            return status;
        }

        bool test_cat_simple( Console &console ) {
            rp::Cat *cat = new rp::Cat( new rp::Literal("a"), new rp::Literal("b"));
            console << test_title("Concatenation (simple)",cat);
            bool status = tr(cat,"",false);
                 status &= tr(cat,"ab",true);
                 status &= tr(cat,"aab",false);
                 status &= tr(cat,"abb",false);
            console << "\n";
            delete cat;
            return status;
        }

        bool test_cat(Console &console) {
            rp::Cat *cat = new rp::Cat(new rp::Plus(literal("a")),new rp::Star(literal("b")));
            console << test_title("Concatenation", cat);
            bool status  = tr(cat,"",false);
                 status &= tr(cat,"a",true);
                 status &= tr(cat,"ab",true);
                 status &= tr(cat,"aaaaa",true);
                 status &= tr(cat,"aaac",false);
                 status &= tr(cat,"aaaab",true);
                 status &= tr(cat,"abbbb",true);
            console << "\n";
            delete cat;
            return status;
        }

        bool test_repeat_n(Console &console) {
            rp::NTimes *p = new rp::NTimes(3,literal("a"));
            
            console << test_title("Repetition",p);
            bool status  = tr(p,   "",        false);
                 status &= tr(p,   "a",       false);
                 status &= tr(p,   "ab",      false);
                 status &= tr(p,   "aaaaa",   false);
                 status &= tr(p,   "aaaa",    false);
                 status &= tr(p,   "aaa",     true);
                 status &= tr(p,   "abbbb",   false);
            console << "\n";
            delete p;
            return status;
        }

        bool test_maybe( Console &console ) {
            rp::Maybe *m = rp::maybe( rp::literal("+"));
            console << test_title("Maybe",m);
            bool status  = tr(m, "",  true);
                 status &= tr(m, "+", true);
                 status &= tr(m, "++", false);
            console << "\n";
            delete m;
            return status;
        }

        void patterns_demo() {
            Console console(std::cout);
            console << "Pattern matching!" << "\n";
            console << "=================" << "\n";
            console << "Every typed object has one or more patterns which serve to generate" "\n";
            console << "both parsing and serializing functionality. This is a demonstration " "\n";
            console << "of some of the parts that are working.\n\n";

            test_whitespace(console);
            test_literal(console);
            test_star(console);
            test_cat_simple(console);
            test_cat(console);
            test_repeat_n(console);
            test_or(console);
            test_maybe(console);

            // eat the '\n'
            console.termios_getch(false);
            // wait for the any key
            console.termios_getch(false);
            
        }
    }
}