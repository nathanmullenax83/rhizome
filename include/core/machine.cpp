#include "machine.hpp"

namespace rhizome {
    namespace core {
        UnaryOperation::UnaryOperation( string const &name, string const &docstring, UnaryOperation::FnPattern f ) 
        : name(name), docstring(docstring), fn(f) {

        }

        

        UnaryOperation::UnaryOperation(): name(""), docstring("") {

        }

        BinaryOperation::BinaryOperation( string const &name, string const &docstring, BinaryOperation::FnPattern f )
        : name(name), docstring(docstring), fn(f) {

        }

        BinaryOperation::BinaryOperation(): name(""), docstring("") {

        }

        UnaryConstraint::UnaryConstraint( string const &name, string const &docstring, UnaryConstraint::FnPattern f ) 
        : name(name), docstring(docstring), fn(f) {

        }

        UnaryConstraint::UnaryConstraint(): name(""), docstring("") {

        }

        bool
        UnaryConstraint::check( Thing * t) {
            return fn(t);
        }

        BinaryConstraint::BinaryConstraint(): name(""), docstring("") {

        }

        BinaryConstraint::BinaryConstraint( string const &name, string const &docstring, BinaryConstraint::FnPattern f ) 
        : name(name), docstring(docstring), fn(f) {

        }

        bool
        BinaryConstraint::check( Thing *a, Thing *b ) {
            return fn(a,b);
        }


        Machine::Machine() {
            
        }

        

        void Machine::push_r( Thing * t) {
            if( check_constraints(t)) {
                ts.push_back(t);
            } else {
                throw runtime_error("push_t: type constraint violated.");
            }
        }

        void Machine::push_l( Thing *t ) {
            if( check_constraints(t)) {
                ts.push_front(t);
            } else {
                throw runtime_error("push_l: type constraint violated.");
            }
            ts.push_front(t);
        }

        void Machine::UnaryOp( string const &name, string const &docstring, function<Thing*(Thing*)> f ) {
            unary_ops[name] = UnaryOperation(name,docstring,f);
        }

        void Machine::BinaryOp( string const &name, string const &docstring, function<Thing*(Thing*,Thing*)> f ) {
            binary_ops[name] = BinaryOperation(name,docstring,f);
        }

        void Machine::constraint( string const &name, string const &docstring, UnaryConstraint::FnPattern f ) {
            unary_constraints[name] = UnaryConstraint(name,docstring,f);
        }

        void Machine::constraint( string const &name, string const &docstring, BinaryConstraint::FnPattern f ) {
            binary_constraints[name] = BinaryConstraint(name,docstring,f);
        }

        void Machine::map_in_place(string const &name) {
            if( unary_ops.count(name)==0 ) {
                throw runtime_error("No such unary operation.");
            }
            auto f = unary_ops[name];
            for(size_t i=0; i<ts.size(); ++i) {
                Thing *temp = ts[i];
                ts[i] = f.fn(ts[i]);
                delete temp;
            }
        }

        void Machine::copy_l() {
            if( ts.size() == 0 ) {
                throw runtime_error("copy_l: empty deque.");
            }
            ts.push_front(ts.front()->clone());
        }

        void Machine::copy_r() {
            if( ts.size() == 0 ) {
                throw runtime_error("copy_r: empty deque.");
            }
            ts.push_back( ts.back()->clone());
        }

        bool Machine::check_constraints( Thing *t ) {
            auto stringify = []( Thing const * const t ) {
                stringstream ss;
                t->serialize_to(ss);
                return ss.str();
            };
            for(size_t i=0; i<machine_constraints.size();++i) {
                UnaryConstraint uc = unary_constraints[machine_constraints[i]];
                if( !uc.check(t)) {
                    stringstream err;
                    err << "Machine constraint not satisfied: \n";
                    err << "\t" << uc.name << ": " << uc.docstring << '\n';
                    err << "\tParameter: " << stringify(t) << '\n';
                    throw runtime_error(err.str());
                }
            }
            return true;
        }

        string Machine::rhizome_type() const {
            return "Machine";
        }

        bool Machine::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }

        void Machine::serialize_to( std::ostream &out ) const {
            out << rhizome_type() << "(";

            out << ")";
        }

        Thing * Machine::clone() const {
            Machine *copy = new Machine(*this);
            return copy;
        }

        Thing * Machine::invoke( string const &method, Thing *arg ) {
            (void)method; (void)arg;
            throw runtime_error("Not implemented.");
        }
    }
}