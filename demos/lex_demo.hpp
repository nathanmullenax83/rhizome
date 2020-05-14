#ifndef RHIZOME_DEMO_LEX
#define RHIZOME_DEMO_LEX

#include <iostream>
#include <sstream>
#include "rhizome.hpp"

using std::stringstream;
using rhizome::lex::Lexer;
using rhizome::parse::Parser;

namespace rp = rhizome::pattern;
namespace rlex = rhizome::lex;

namespace rhizome {
    namespace demo {
        void lex_demo();
    }
}

#endif
