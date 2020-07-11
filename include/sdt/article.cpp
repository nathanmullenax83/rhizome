#include "article.hpp"

namespace rhizome {
    namespace sdt {
        Article::Article() {

        }

        string Article::HumanName() const {
            return "article";
        }

        string Article::InternalName() const {
            return "rhizome::sdt::Article";
        }
    }
}