#include "choice_of_several.hpp"
#include <cassert>

using rhizome::core::indent;
using rhizome::core::Dispatcher;

namespace rhizome {
    namespace sdt {

        namespace cos {
            static Dispatcher<ChoiceOfSeveral> dispatcher({
                {
                    "choose", []( Thing *context,ChoiceOfSeveral *that, Thing *arg ) {
                        assert( arg!=NULL && arg->rhizome_type()=="String");
                        String *s = (String*)arg;
                        that->choose(context, s->native_string());
                        return (Thing*)NULL;
                    }
                }
            });
        }

        ChoiceOfSeveral::ChoiceOfSeveral( Parser *parser ): parser(parser) {

        }

        ChoiceOfSeveral::~ChoiceOfSeveral() {
            for( auto i=actions.begin(); i!=actions.end(); i++){
                delete i->second;
            }
            // this really isn't necessary, but just to be clear:
            actions.clear();
            listeners.clear();
            options.clear();
            parser = NULL;
        }
        
        ChoiceOfSeveral &
        ChoiceOfSeveral::define_choice( string const &id, string const &desc, string const &action ) {
            Thing * s = parser->parse_thing("Statement",action);
            assert( s->has_interface("statement") );
            Statement *statement = (Statement*)s;
            if( actions.count(id) > 0) {
                delete actions.at(id);
            }
            actions[id] = statement;
            options.push_back( pair<string,string>(id,desc));
            return *this;
        }

        ChoiceOfSeveral &
        ChoiceOfSeveral::define_event_listener(string const &id, Thing *recipient) {
            listeners[id].push_back(recipient);
            return *this;
        }

        ChoiceOfSeveral & 
        ChoiceOfSeveral::choose( Thing *context, string const &id ) {
            Thing * result = actions[id]->evaluate(context);
            if( listeners.count(id) > 0) {
                for( auto i=listeners.at(id).begin(); i!= listeners.at(id).end(); i++) {
                    Thing *result_copy = result->clone();
                    (*i)->invoke(context,"choose",result_copy);
                    delete result_copy;
                }
            }
            return *this;
        }

        vector<Choice>
        ChoiceOfSeveral::choices() const {
            return options;
        }

        string 
        ChoiceOfSeveral::rhizome_type() const {
            return "Choice";
        }

        void
        ChoiceOfSeveral::serialize_to(size_t level, std::ostream &out) const {
            out << indent(level) << rhizome_type() << "{\n";
            throw runtime_error("Not implemented.");
            out << indent(level) << "}\n";
        }

        bool
        ChoiceOfSeveral::has_interface( string const &name ) {
            return name=="Thing"||name==rhizome_type()||name=="sdt";
        }

        Thing *
        ChoiceOfSeveral::clone() const {
            // note: using the same parser.
            ChoiceOfSeveral *cos = new ChoiceOfSeveral(parser);
            cos->options = options;
            for( auto i=actions.begin(); i!=actions.end(); i++) {
                cos->actions.emplace(i->first,(Statement*)i->second->clone());
            }
            cos->listeners = listeners;
            return cos;
        }

        Thing *
        ChoiceOfSeveral::invoke( Thing *context, string const &method, Thing *arg ) {
            try {
                return cos::dispatcher.at(method)( context, this, arg );
            } catch( std::exception *e ) {
                if( cos::dispatcher.count(method)==0) {
                    throw runtime_error(rhizome::core::invoke_method_not_found(method,this,context));
                } else {
                    throw runtime_error(rhizome::core::invoke_error(method,arg,this,context,e));
                }
            }
        }

    }
}