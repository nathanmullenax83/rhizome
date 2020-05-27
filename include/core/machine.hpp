#ifndef RHIZOME_CORE_MACHINE_HPP
#define RHIZOME_CORE_MACHINE_HPP

#include <deque>
#include <map>
#include <vector>
#include <functional>
#include <string>
#include <stdexcept>
#include <sstream>
#include "core/thing.hpp"

using std::deque;
using std::map;
using std::vector;
using std::function;
using std::string;
using std::runtime_error;
using std::stringstream;

using rhizome::core::Thing;

namespace rhizome {
    namespace core {

        class UnaryConstraint {
        public:
            typedef function< bool(Thing*) > FnPattern;
            
            string name;
            string docstring;
            FnPattern fn;

        public:
            UnaryConstraint();
            UnaryConstraint( string const &name, string const &docstring, FnPattern f);
            bool check( Thing *v );
        };

        class BinaryConstraint {
        public:
            typedef function< bool(Thing*,Thing*) > FnPattern;
            string name;
            string docstring;
            FnPattern fn;

            BinaryConstraint();
            BinaryConstraint( string const &name, string const &docstring, FnPattern f );
            bool check( Thing *a, Thing *b );
        };

        

        class UnaryOperation {
        public:
            typedef function< Thing*(Thing*) > FnPattern;
            vector<string> preconditions;
            vector<string> postconditions;
            string name;
            string docstring;
            FnPattern fn;
        public:
            UnaryOperation();
            UnaryOperation ( string const &name, string const &docstring, FnPattern f );
        };

        class BinaryOperation {
        public:
            typedef function< Thing*(Thing*,Thing*) > FnPattern;
            vector<string> preconditions;
            vector<string> postconditions;
            string name;
            string docstring;
            FnPattern fn;
        public:
            BinaryOperation();
            BinaryOperation( string const &name, string const &docstring, FnPattern f );
        };



        /// What is the relationship between the concrete machine
        /// and the abstract semantic construct? The concrete machine
        /// is the concrete implementation of the algebra of a particular
        /// class of objects. 
        class Machine: public Thing {
        protected:
            
            deque<Thing *> ts;
            
            map < string, UnaryConstraint >     unary_constraints;
            map < string, BinaryConstraint >    binary_constraints;
            map < string, UnaryOperation >      unary_ops;
            map < string, BinaryOperation >     binary_ops;

            vector<string> machine_constraints;
        
            /// Check the conjunction of all type-constraints. 
            bool check_constraints( Thing *t );
        public:
            Machine();
        
            void constraint( string const &name, string const &docstring, UnaryConstraint::FnPattern f );
            void constraint( string const &name, string const &docstring, BinaryConstraint::FnPattern f);
            void UnaryOp( string const &name, string const &docstring, UnaryOperation::FnPattern f );
            void BinaryOp( string const &name, string const &docstring, BinaryOperation::FnPattern f );            

            void push_l( Thing *t );
            void push_r( Thing *t );
            void map_in_place( string const &unary_opname );
            void fold_l( string const &binary_opname );
            void fold_r( string const &binary_opname );

            /// duplicate the left-most element
            void copy_l();
            /// duplicate the right-most element
            void copy_r();

            friend class System;

            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            
            virtual void serialize_to( std::ostream &out ) const override;
            virtual Thing * clone() const override;

            virtual Thing * invoke( string const &method, Thing *arg ) override;

        };
    }
}


#endif
