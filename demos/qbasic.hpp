#ifndef RHIZOME_DEMOS_QBASIC
#define RHIZOME_DEMOS_QBASIC

#include "rhizome.hpp"

using rhizome::lex::Lexer;
using rhizome::parse::Parser;

using namespace rhizome::parse;
using namespace rhizome::types;

namespace rhizome {
    namespace demos {
        Lexer * create_qbasic_lexer();
        Parser * create_qbasic_parser();
    }
}

#endif