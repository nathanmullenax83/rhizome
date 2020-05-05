#include "article.hpp"

namespace rhizome {
    namespace html {
        Article::Article() {

        }

        Article::~Article() {

        }

        void
        Article::write_to( ostream &out ) {
            out << "<article>";
            write_children(out);
            out << "</article>";
        }
    }
}