#ifndef RHIZOME_SDT_CHOICE_OF_SEVERAL
#define RHIZOME_SDT_CHOICE_OF_SEVERAL

/* The point of this task is to represent abstractly a choice of several. 
 * This class is a member of the semantic data type namespace, and as such
 * really only represents structure and data rather than UI configuration.
 */
#include <vector>
#include <map> 
#include <string>
#include <tuple>
using std::vector;
using std::map;
using std::string;
using std::pair;
#include "core/thing.hpp"
#include "types/statement.hpp"
#include "parse.hpp"

using rhizome::core::Thing;
using rhizome::types::Statement;
using rhizome::parse::Parser;

namespace rhizome {
    namespace sdt {
        typedef pair< string, string > Event;
        typedef pair< string, string > Choice; 


        /// This object owns all of the pointers you give it except for the listeners, which
        /// are assumed to have some other scope. The parser, however, is assumed to be owned
        /// by some other object. Ideally, we aren't creating a ton of of those, and this
        /// particular object doesn't directly modify the grammar.          
        class ChoiceOfSeveral: public Thing {
        private:
            Parser *parser;
            map< string, vector<Thing *> > listeners;
            map< string, Statement * > actions;
            vector< Choice > options;
        public:
            // event interpreter parses the content 
            // in this case, the parser should define a non-terminal called "Statement" to generate
            // (you guessed it) Statements and subtypes thereof. The default system parser does this,
            // so unless you have a reason to implement a from-scratch parser, the system-generating 
            // plant() function is the way to go.
            ChoiceOfSeveral(Parser *event_interpreter);

            // Destructor virtual. 
            // I'm going to delete all statements (actions), but listeners and parser are free 
            // and dangling!
            virtual ~ChoiceOfSeveral();

            // would like to express menus in a declarative style.
            // Define a menu item. When 'text' is selected, /id/. 
            // Action is parsed by the non-terminal "Statement"
            ChoiceOfSeveral & define_choice( string const &id, string const &desc, string const &action="" ); 

            // Add an event listener
            ChoiceOfSeveral & define_event_listener( string const &id, Thing *recipient );


            /// This function does several things. It is to be run when something is
            /// picked from a menu. First, if there is an action defined,
            /// it runs that action. It then invokes 'choose' with an argument of ID
            /// and an argument of whatever action->evaluate() produces.
            ChoiceOfSeveral & choose( Thing *context, string const &id );


            /// UI can represent the options however may be conventient for the media
            /// This could be HTML or Console UI.
            vector< Choice > choices() const;



            // thing interface
            virtual string rhizome_type() const override;
            virtual void serialize_to( size_t level, std::ostream &out ) const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * clone() const override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            
        };
    }
}

#endif