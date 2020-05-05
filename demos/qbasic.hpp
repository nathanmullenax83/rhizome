#ifndef RHIZOME_DEMOS_QBASIC
#define RHIZOME_DEMOS_QBASIC

#include "types.hpp"
#include "parse.hpp"
#include "core/i_plugin.hpp"
#include "core/machine.hpp"

using rhizome::core::IPlugin;
using rhizome::core::Machine;
using rhizome::parse::Parser;
using namespace rhizome::parse;
using namespace rhizome::types;

namespace rhizome {
    namespace demos {
        class QBasic: public IPlugin {
        private:
            Machine vm;

            IParser * create_parser();

        public:
            virtual void rhizome_load() override;
            
            virtual void rhizome_unload() override;
        };
    }
}

#endif