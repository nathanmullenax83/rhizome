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

        typedef function<bool(Console &)> Test;

        bool tr(Pattern * p, string const &s, bool expected ) {
            bool a = p->accepts(s);
            string pass(rl::green("Pass"));
            string fail(rl::red("Fail"));
            std::cout << exactly(20,s,true) << exactly(20,(a ? "Accepted" : "Rejected"));
            std::cout << (a==expected ? pass : fail ) << std::endl;
            return a==expected;
        }

        bool test_whitespace(Console &console) {
            rp::Pattern *p = whitespace_plus();
            console << "Whitespace pattern: ";
            p->serialize_to(std::cout);
            console << "\n";
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
            console << "Literal 'test':\n";
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
            p->add_clause(literal("one"));
            p->add_clause(literal("two"));
            p->add_clause(literal("three"));
            p->add_clause(literal("four"));
            console << "p = ";
            p->serialize_to(std::cout);
            console << "\n";
            bool status  = tr(p,"one",     true);
                 status &= tr(p,"two",     true);
                 status &= tr(p,"five",    false);
                 status &= tr(p,"on",      false);
                 status &= tr(p,"_three",  false);
                 status &= tr(p,"three",   true);
            console << "\n";
            delete p;
            return status;
        }

        bool test_star(Console &console) {
            rp::Pattern *star = new rp::Star(literal("a"));
            console << "Repetition: ";
            star->serialize_to(std::cout);
            console << "\n";
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

        bool test_cat(Console &console) {
            rp::Cat *cat = new rp::Cat(new rp::Plus(literal("a")),new rp::Star(literal("b")));
            console << "Concatenation: ";
            cat->serialize_to(std::cout);
            console << "\n";
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
            console << "Repetition: a{3}\n";
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
            test_or(console);
            test_cat(console);
            test_repeat_n(console);
        }
    }
}