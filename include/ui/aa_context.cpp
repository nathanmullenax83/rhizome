#include "aa_context.hpp"

namespace rhizome {
    namespace ui {
        AAContext::AAContext() {
            context = aa_autoinit(&aa_defparams);
            if ( context==NULL ) {
                throw runtime_error("Couldn't initialize AALib context.");
            }
        }

        AAContext::~AAContext() {
            aa_close(context);
        }
    }
}