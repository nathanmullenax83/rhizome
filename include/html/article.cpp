#include "article.hpp"

namespace rhizome {
    namespace html {
        Article::Article() {

        }

        Article::~Article() {

        }

        void
        Article::write_to( ostream &out, size_t indent ) {
            out << "<article>";
            write_children(out, indent+1);
            out << "</article>";
        }
    }
}