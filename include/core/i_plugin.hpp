#ifndef RHIZOME_CORE_I_PLUGIN
#define RHIZOME_CORE_I_PLUGIN

namespace rhizome {
    namespace core {
        /// If you want to make runtime accessible to rhizome,
        /// implement this.
        class IPlugin {
        public:
            /// Loading hooks for your plugin. This is where you might configure
            /// the compiler, define custom types, and if necessary initialize 
            /// external runtime (e.g., ncurses_init)
            virtual void rhizome_load() = 0;

            /// Pop parser configuration, delete stuff. 
            virtual void rhizome_unload() = 0;
        };
    }
}

#endif 
