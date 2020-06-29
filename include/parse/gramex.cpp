#include "gramex.hpp"

#include "log.hpp"

namespace rhizome {
    namespace parse {
        Gramex::~Gramex() {

        }

        Gramex::Gramex(): matched_tokens({}) {

        }

        void
        Gramex::append_all( deque<Thing *> ts ) {
            //static rhizome::log::Log log("gramex_append_all");
            //log.info("Appending tokens.");
            
            for( size_t i=0; i<ts.size(); ++i) {
                // stringstream t; t<< i << ": Appending '";
                // ts[i]->serialize_to(t);
                // t << "'";
                //log.info(t.str());

                matched_tokens.push_back(ts[i]);
            }
        }

        void
        Gramex::clear() {
            // delete matches
            //static rhizome::log::Log log("gramex_clear");
            //log.info("Clearing gramex.");
            for(size_t i=0; i<matched_tokens.size(); ++i) {
                if( matched_tokens[i]!=NULL ) {
                    delete matched_tokens[i];
                    matched_tokens[i] = NULL;
                    //log.info("Deleted 1 matched token.");
                } else {
                    //log.info("A matched token is NULL.");
                }
            }
            matched_tokens.clear();
        }

        deque<Thing*>
        Gramex::clone_matched_tokens() const {
            deque<Thing*> copy;
            for(size_t i=0; i<matched_tokens.size(); ++i) {
                copy.push_back( matched_tokens[i]->clone() );
            }
            return copy;
        }

        Thing *
        Gramex::clone() const {
            return (Thing*)clone_gramex(true);
        }

        size_t
        Gramex::match_count() const {
            return matched_tokens.size();
        }
    }
}