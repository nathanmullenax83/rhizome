#ifndef RHIZOME_SDT_ARTICLE_HPP
#define RHIZOME_SDT_ARTICLE_HPP

#include <string>
#include <deque>

#include "core/thing.hpp"
#include "sdt.hpp"
#include "paragraph.hpp"


using std::deque;
using std::string;
using rhizome::sdt::Paragraph;


namespace rhizome {
    namespace sdt {
        class Article: public SDT {
        private:
            deque<Paragraph> paragraphs_relentless;
        public:
            Article();

            string title;

            virtual string HumanName() const override;
            virtual string InternalName() const override;

            
        };
    }
}

#endif