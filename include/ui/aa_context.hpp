#ifndef RHIZOME_UI_AA_CONTEXT_HPP
#define RHIZOME_UI_AA_CONTEXT_HPP

#include <stdexcept>
#include <aalib.h>

using std::runtime_error;

namespace rhizome {
    namespace ui {
        class AAContext {
        private:
            aa_context *context;
        public:
            AAContext();
            virtual ~AAContext();

            
        };
    }
}

#endif
