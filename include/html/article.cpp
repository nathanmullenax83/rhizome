#include "article.hpp"

using rhizome::core::indent;

namespace rhizome {
    namespace html {
        Article::Article() {

        }

        Article::~Article() {

        }

        void
        Article::write_to( ostream &out, size_t level ) const {
            out << indent(level) << "<article>\n";
            write_children(out, level+1);
            out << indent(level) << "</article>\n";
        }
    }
}