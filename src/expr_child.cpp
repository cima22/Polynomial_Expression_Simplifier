#include "expr_child.h"
#include <string>

// Definition of VarExpr class ---------------------------------------------------------------------------------
// (few methods of class VarExpr are defined afterward, in order to group the definitions of different derived classes togheter)

VarExpr::VarExpr(const Var& v):
	ParentExpr(v.get_name(),{v}){}

void VarExpr::set_value(int v){
	vars[0].set_value(v);
}

const VarExpr& VarExpr::stretch() const { // There is no need to stretch, it is sufficient to return a copy of the object
	return * new VarExpr{*this};
}

const VarExpr& VarExpr::extend() const { // There is no need to extend
	return * new VarExpr{*this}; 
}

const VarExpr& VarExpr::clone() const{
	return * new VarExpr{*this};
}

bool VarExpr::is_only_mult() const{ // A single variable is always a monomial
	return true;
}

int VarExpr::get_degree(const Var& v) const{ // returns 1 only if the variable is the same
	return v == vars[0] ? 1 : 0;
}

VarExpr::~VarExpr() = default; // default destructor is ok

bool VarExpr::is_extended() const { // a variable is always a monomial
	return true;
}

const ParentExpr& VarExpr::extract_monomial(const Var& v) const { // extract the monomial that multiplies the variable (in this case either the variable itslef or 1)
	if(vars[0] == v)
		return * new ConstExpr{1};
	return this->clone();
}

std::map<unsigned int, const ParentExpr*> VarExpr::get_coeffs(const Var& v) const { // return the coefficients of a variable is trivial
	std::map<unsigned int,const ParentExpr*> coeffs{};
	bool is_same_var = v == vars[0];
	if(is_same_var){
		ConstExpr* g_1 = new ConstExpr{1};
		coeffs.insert({1,g_1});
	}
	return coeffs;
}

void VarExpr::insert_coeff(std::map<unsigned int, const ParentExpr*>& coeffs, const Var& v) const{ // inserts into an existing map the coefficient relative to variable v. If a coefficient with the same degree
												   // is present, then it sums the coefficients. 
	bool is_same_var = vars[0] == v;
	int degree       = is_same_var ? 1 : 0;
	std::map<unsigned int, const ParentExpr*>::iterator present = coeffs.find(degree); // check if a coefficient with the same degree is already present
	const ParentExpr* new_sub = &extract_monomial(v);

	if(present != coeffs.end()){ // if the another coefficient with that degree is already present, sum the two to obtain the new coefficient
		const ParentExpr* new_coeff = new CompExpr{*coeffs[degree],*new_sub,operation::sum};
		present->second = new_coeff;
	}
	else{
		coeffs.insert({degree,new_sub});
	}
}


const ParentExpr& VarExpr::replace(const std::map<Var,const ParentExpr*>& repl) const { // replace the variable with another expression
	bool present = repl.find(vars[0]) != repl.end();
	if(!present) // if the variables has not to be replaced, return a copy of it
		return this->clone(); 
	return repl.at(vars[0])->clone(); // return a copy of the expression wich should replace the variable
}

bool VarExpr::is_VarExpr(const ParentExpr& ex){ return dynamic_cast<const VarExpr*>(&ex); } // tries to cast the parent reference to a VarExpr reference

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// Definition of VarExpr class ------------------------------------------------------------------------------------------------------------------------------
// (few methods of class VarExpr are defined afterward, in order to group the definitions of different derived classes together)

ConstExpr::ConstExpr(const int i):
	value{i},ParentExpr(std::to_string(i)){}

const ConstExpr& ConstExpr::stretch() const {
	return * new ConstExpr{*this};
}

const ConstExpr& ConstExpr::extend() const {
	return *this;
}

bool ConstExpr::is_extended() const {
	return true;
}

bool ConstExpr::is_only_mult() const{
	return true;
}

int ConstExpr::get_degree(const Var& v) const {
	return 0;
}

const ConstExpr& ConstExpr::clone() const{
	return * new ConstExpr{*this};
}

ConstExpr::~ConstExpr() = default;

std::map<unsigned int, const ParentExpr*> ConstExpr::get_coeffs(const Var& v) const { // the map that has to be returned is empty, there are no coefficient for any variable
	return std::map<unsigned int, const ParentExpr*>{};
}

void ConstExpr::insert_coeff(std::map<unsigned int, const ParentExpr*>& coeffs, const Var& v) const{ // insert the constant in an existing map with degree 0. Sums to an existing coefficient, if any
	std::map<unsigned int, const ParentExpr*>::iterator present = coeffs.find(0);
	const ParentExpr* new_coeff;
	if(present != coeffs.end()){
		new_coeff = new CompExpr{*coeffs[0],clone(),operation::sum};
		present->second = new_coeff;
	}
	else{
		new_coeff = &clone();
		coeffs.insert({0,new_coeff});
	}
}

const ConstExpr& ConstExpr::extract_monomial(const Var& v) const {
	return this->clone();
}

const ParentExpr& ConstExpr::replace(const std::map<Var,const ParentExpr*>& repl) const {
	return this->clone();
}

bool ConstExpr::is_ConstExpr(const ParentExpr& ex){ return dynamic_cast<const ConstExpr*>(&ex); }

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// Definition of CompExpr class ------------------------------------------------------------------------------------------------------------------------------

std::string CompExpr::create_string(const ParentExpr& e1, const ParentExpr& e2, const operation op){ // given two sub-expr and an operation, constructs the string format of the expression
	char op_c;
	switch(op){
		case operation::sum:
			op_c = '+';
			break;
		case operation::sub:
			op_c = '-';
			break;
		case operation::mul:
			op_c = '*';
			break;
		default:
			op_c = '?';
			break;
	}
	return std::string{e1.to_string() + " " + op_c + " " + e2.to_string()};
}

bool CompExpr::is_CompExpr(const ParentExpr& ex) { return dynamic_cast<const CompExpr*>(&ex); }

CompExpr::CompExpr(const ParentExpr& e1, const ParentExpr& e2, const operation op):
	sub_1{e1}, sub_2{e2}, op{op}, ParentExpr(create_string(e1,e2,op))
	{}

CompExpr::CompExpr(const std::string& expr, const ParentExpr& e1, const ParentExpr& e2, operation op): // constructor with a custom string format
	sub_1{e1},sub_2{e2},op{op},ParentExpr(expr)
	{}

CompExpr::CompExpr(const std::string& expr, const std::vector<Var>& vars, const ParentExpr& e1, const ParentExpr& e2, operation op): // constructor with custom string format and vector of variables
	sub_1{e1},sub_2{e2},op{op},ParentExpr(expr,vars)
	{}

CompExpr::CompExpr(const CompExpr& comp): // copy constructor where also the sub expressions are copied
	sub_1{comp.get_sub_1().clone()},sub_2{comp.get_sub_2().clone()},op{comp.get_op()},ParentExpr(comp){}

CompExpr::~CompExpr(){ // destructor of CompExpr. There must be deleted also the sub expressions
	delete &sub_1;
	delete &sub_2;
}

// Static methods

const ParentExpr& CompExpr::create_monomial(const Var& v, unsigned int degree) { // recursively creates v**degree
	if(degree == 0)
		return * new ConstExpr{1};
	const VarExpr& var = * new VarExpr{v};
	if(degree == 1)
		return var;
	return * new CompExpr{var,create_monomial(v,degree - 1),operation::mul};
};

// End of static methods

const operation CompExpr::get_op()      const { return op; }
const ParentExpr& CompExpr::get_sub_1() const { return sub_1; }
const ParentExpr& CompExpr::get_sub_2() const { return sub_2; }

const CompExpr& CompExpr::clone() const{ // creates a clone of the comp expression, cloning also the sub expressions
	const ParentExpr& clone_sub_1 = sub_1.clone();
	const ParentExpr& clone_sub_2 = sub_2.clone();
	return * new CompExpr{clone_sub_1,clone_sub_2,op};
}

std::map<unsigned int, const ParentExpr*> CompExpr::get_coeffs(const Var& v) const { // returns the non-null coefficients in respect to the variable x
	std::map<unsigned int,const ParentExpr*> coeffs{};
	const CompExpr& extended = dynamic_cast<const CompExpr&>(extend()); // perform the extension of the expression so to have it in a form of sum of monomials
	switch(extended.get_op()){
		case operation::mul: // if the extended expression is a multiplication, than it is a monomial, so we can insert the corresponding coefficient in the map
			extended.insert_coeff(coeffs,v);
			break;
		case operation::sum:{ // if the extended expression is a sum, than there could be two cases: either one sub expression is a monomial and the other is a sum of monomials or it is just
				      // a sum of two monomials.
			const ParentExpr& ext_sub_1 = extended.get_sub_1();
			const ParentExpr& ext_sub_2 = extended.get_sub_2();
			bool is_only_mult_1 = ext_sub_1.is_only_mult(); // check if first sub expr is a monomial
			bool is_only_mult_2 = ext_sub_2.is_only_mult(); // check if second sub expr is a monomial

			if(is_only_mult_1 != is_only_mult_2){ // if one of the sub expr is a sum of monomials
				const ParentExpr& ext_sub = is_only_mult_1 ? ext_sub_2 : ext_sub_1;
				coeffs = ext_sub.get_coeffs(v); // get the map of the coefficient of the rest of the sum of monomials
			}
	
			if(is_only_mult_1) // if sub expr 1 is a monomial, insert it into the map
				ext_sub_1.insert_coeff(coeffs,v);
			if(is_only_mult_2) // if sub expr 2 is a monomial, insert it into the map
				ext_sub_2.insert_coeff(coeffs,v);
			break;
		}
		default:
			break;
	}
	delete &extended; // delete the extended expression genereted
	return coeffs;
}

void CompExpr::insert_coeff(std::map<unsigned int, const ParentExpr*>& coeffs, const Var &v) const { // insert the coefficient of the monomial relative to the variable into the map
	if(!is_only_mult())
		throw NotMonomial{}; // Throw NotMonomial exception if this funciton is used with a non monomial expression
	int degree = get_degree(v); // get the degree of the variable in the monomial
	const ParentExpr& new_monomial = extract_monomial(v); // extract the monomial that multiplies the power of the variable
	std::map<unsigned int,const ParentExpr*>::iterator present = coeffs.find(degree); // find if a coefficient with that degree is already present in the map
	const ParentExpr* new_coeff = &new_monomial;
	if(present != coeffs.end()){ // if it is present, sum the two to obtain the new coefficient
		new_coeff = new CompExpr{*coeffs[degree],new_monomial,operation::sum};
		present->second = new_coeff;
	}
	coeffs.insert({degree,new_coeff});
}

int CompExpr::get_degree(const Var& v) const { // the degree of the monomial in respect to the variable is the sum of the degree of the monomial in the sub expressions
	return sub_1.get_degree(v) + sub_2.get_degree(v);	
	if(!is_only_mult())
		throw NotMonomial{}; // Throw NotMonomial exception if this funciton is used with a non monomial expression
}

const ParentExpr& CompExpr::extract_monomial(const Var& v) const { // extract the monomial part that multiplies the power of the variable in the monomial
	bool is_var_1 = VarExpr::is_VarExpr(sub_1);//dynamic_cast<const VarExpr*>(&sub_1);
	bool is_var_2 = VarExpr::is_VarExpr(sub_2);//dynamic_cast<const VarExpr*>(&sub_2);
	if(is_var_1 || is_var_2){ // if at least one of the sub expr is a variable
		const VarExpr& var = is_var_1 ? dynamic_cast<const VarExpr&>(sub_1) : dynamic_cast<const VarExpr&>(sub_2); // get the variable sub expr
		const ParentExpr& other_sub = is_var_1 ? sub_2 : sub_1; // get the other sub expr that may be a variable or not
		if(var.get_variables()[0] == v) // if the variable part is the same variable for which we are searching the monomial
			return other_sub.extract_monomial(v); // extract just the monomial part in the other sub expression
		return * new CompExpr{var.clone(),other_sub.extract_monomial(v),operation::mul}; 
	
	}
	return * new CompExpr{sub_1.extract_monomial(v),sub_2.extract_monomial(v),operation::mul}; // if both sub expr are comp expr, return the multiplication of the two monomial extracted 
}

const ParentExpr& CompExpr::replace(const std::map<Var,const ParentExpr*>& repl) const { // replaces every occurence of a variable by the specified expression
	const ParentExpr& new_sub_1 = sub_1.replace(repl); // it is simply needed to replace the variables in the sub-expressions
	const ParentExpr& new_sub_2 = sub_2.replace(repl);
	bool is_comp_expr_1 = is_CompExpr(new_sub_1); // check if the sub expressions are comp expr, just to eventually put brackets in the string format
	bool is_comp_expr_2 = is_CompExpr(new_sub_2);
	std::string str_1 = is_comp_expr_1 ? "(" + new_sub_1.to_string() + ") " : new_sub_1.to_string() + " ";
	std::string str_2 = is_comp_expr_2 ? " (" + new_sub_2.to_string() + ")" : " " + new_sub_2.to_string();
	char op_c = get_op() == operation::sum ? '+' : '*';
	std::string str = str_1 + op_c + str_2; 
	return * new CompExpr{str,new_sub_1,new_sub_2,get_op()}; // return the same operation but with replaced sub expressions
}

// Methods to compute the operation in the compound expression

const CompExpr& CompExpr::compute_operation(){ // computes the operation indicated by op, returning an equivalent expression
	
	bool is_comp_expr_1 = is_CompExpr(sub_1);	// wether the first sub-expression is simple or compound
	bool is_comp_expr_2 = is_CompExpr(sub_2);	// idem for the second sub-expr
	
	if(!is_comp_expr_1 && !is_comp_expr_2) // return a copy of the expression if the sub-expressions are simple	
		return * new CompExpr{*this};
	
	if(is_comp_expr_1 != is_comp_expr_2){		// if one sub-expr is simple and the other is compound
		switch(op){
			case operation::sum:
				return this->sum_simple_comp(); // return the sum
			case operation::mul:
				return this->mult_simple_comp(); // return the multiplication (distributive or associative law)
			default:
				return *this;
		}
	}

	// At this point, we are sure that we have to deal with two compound sub-expressions
	switch(op){
		case operation::sum:
			return this->compound_sum();	// we have either to compute a compound sum
		case operation::mul:
			return this->compound_mult();	// or a compound multiplication
		default:
			return *this;
	}
	
}

const CompExpr& CompExpr::sum_simple_comp(){ // sum between simple expr and comp expr
	bool is_comp_expr_1 = is_CompExpr(sub_1);
	const CompExpr& sub_comp = is_comp_expr_1 ? dynamic_cast<const CompExpr&>(sub_1) : dynamic_cast<const CompExpr&>(sub_2);
	const ParentExpr& sub    = is_comp_expr_1 ? sub_2 : sub_1;
	return * new CompExpr{sub.clone(),sub_comp.clone(),operation::sum}; // rearrange the expression to have the simple expression as first sub expr
}

const CompExpr& CompExpr::compound_sum(){ // sum between to comp expr
	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	operation op_sub_1   = comp_sub_1.get_op();
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);
	operation op_sub_2   = comp_sub_2.get_op();

	if(op_sub_1 == operation::sum && op_sub_2 == operation::sum)
		return this->sum_sum();
	if(op_sub_1 == operation::mul && op_sub_2 == operation::mul)
		return this->sum_mult();
	return this->sum_mixed();
}

const CompExpr& CompExpr::sum_sum(){ // sum of two sum-comp expr. Returns an equivalent expression using the associative law
	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);
	const CompExpr& sum_2 = * new CompExpr{comp_sub_1.get_sub_2().clone(),comp_sub_2.clone(),operation::sum};
	const CompExpr& sum_1 = * new CompExpr{comp_sub_1.get_sub_1().clone(),sum_2,operation::sum};

	return sum_1;
}

const CompExpr& CompExpr::sum_mult(){ // in this case it is sufficient to return a copy of the expression
	return this->clone();
	/*
	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);
	return * new CompExpr{comp_sub_1.clone(),comp_sub_2.clone(),operation::sum};*/
}

const CompExpr& CompExpr::sum_mixed(){ // sum of one sum-comp expr and one mult-comp expr. Returns an equivalent expression using the associative law
	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);
	bool is_first_sum = comp_sub_1.get_op() == operation::sum; // is the first sub expr a sum or the second?

	const ParentExpr& new_sub_1_1 = is_first_sum ? comp_sub_1.get_sub_1() : comp_sub_2.get_sub_1();
	const ParentExpr& new_sub_1_2 = is_first_sum ? comp_sub_1.get_sub_2() : comp_sub_2.get_sub_2();
	const CompExpr& new_mem_2    = is_first_sum ? comp_sub_2 : comp_sub_1;

	const ParentExpr& sum_2 = * new CompExpr{new_sub_1_2.clone(),new_mem_2.clone(),operation::sum};

	return * new CompExpr{new_sub_1_1.clone(),sum_2,operation::sum};
}

const CompExpr& CompExpr::mult_simple_comp(){ // multiplication of a simple expr and a comp expr
	bool is_comp_expr_1 = is_CompExpr(sub_1);
	const CompExpr& sub_comp = is_comp_expr_1 ? dynamic_cast<const CompExpr&>(sub_1) : dynamic_cast<const CompExpr&>(sub_2);
	const ParentExpr& sub_simple = is_comp_expr_1 ? sub_2 : sub_1;
	operation sub_op = sub_comp.get_op();
	switch(sub_op){ // different behavoiur accordingly to the operation of the sub comp expr
		case operation::sum:
			return this->distr_law(); // distributive law
		case operation::mul:{ // put the simple expr as first sub expr
			return * new CompExpr{sub_simple.clone(),sub_comp.clone(),op};
		    }
		default:
			return this->clone();
	}
}

const CompExpr& CompExpr::distr_law(){ // the distributive law
	bool is_comp_expr_1 = is_CompExpr(sub_1);
	const CompExpr& comp_sub = is_comp_expr_1 ? dynamic_cast<const CompExpr&>(sub_1) : dynamic_cast<const CompExpr&>(sub_2);
	const ParentExpr& simple_sub = is_comp_expr_1 ? sub_2 : sub_1;

	const ParentExpr& new_sub_1 = * new CompExpr{simple_sub.clone(),comp_sub.get_sub_1().clone(),operation::mul};
	const ParentExpr& new_sub_2 = * new CompExpr{simple_sub.clone(),comp_sub.get_sub_2().clone(),operation::mul};

	return * new CompExpr{new_sub_1,new_sub_2,operation::sum};
}

const CompExpr& CompExpr::compound_mult(){ // multiplication between two comp expr
	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	operation op_sub_1   = comp_sub_1.get_op();
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);
	operation op_sub_2   = comp_sub_2.get_op();

	if(op_sub_1 == operation::sum && op_sub_2 == operation::sum)
		return this->mult_sum();
	if(op_sub_1 == operation::mul && op_sub_2 == operation::mul)
		return this->mult_mult();
	return this->mult_mixed();
}

const CompExpr& CompExpr::mult_sum(){ // multiplication between two sums; must distribute the sums: (a + b) * (c + d)

	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);

	const CompExpr&   mul_1_1   = * new CompExpr{comp_sub_1.get_sub_1().clone(),comp_sub_2.get_sub_1().clone(),operation::mul}; // a * c
	const CompExpr&   mul_1_2   = * new CompExpr{comp_sub_1.get_sub_1().clone(),comp_sub_2.get_sub_2().clone(),operation::mul}; // a * d
		
	const CompExpr&   mul_2_1   = * new CompExpr{comp_sub_1.get_sub_2().clone(),comp_sub_2.get_sub_1().clone(),operation::mul}; // b * c
	const CompExpr&   mul_2_2   = * new CompExpr{comp_sub_1.get_sub_2().clone(),comp_sub_2.get_sub_2().clone(),operation::mul}; // b * d
		
	const CompExpr&     sum_3   = * new CompExpr{mul_2_1,mul_2_2,operation::sum}; // (b * c) + (b * d)
	const CompExpr&     sum_2   = * new CompExpr{mul_1_2,sum_3,operation::sum};   // (a * d) + ((b * c) + (b * d))
	const CompExpr&     sum_1   = * new CompExpr{mul_1_1,sum_2,operation::sum};   // (a * c) + ((a * d) * ((b * c) + (b * d)))

	return sum_1;
}

const CompExpr& CompExpr::mult_mult(){ // multiplication between two mult comp expr; use associative law
	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);

	const CompExpr& mul_2 = * new CompExpr{comp_sub_1.get_sub_2().clone(),comp_sub_2.clone(),operation::mul};
	const CompExpr& mul_1 = * new CompExpr{comp_sub_1.get_sub_1().clone(),mul_2,operation::mul};

	return mul_1;
}

const CompExpr& CompExpr::mult_mixed(){ // multiplication between one sum-comp expr and one mult-comp expr; must distribute the sum: (a + b) * (c * d)
	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);
	bool is_first_sum    = comp_sub_1.get_op() == operation::sum;
	const ParentExpr& new_sub_1_1    = is_first_sum ? comp_sub_1.get_sub_1() : comp_sub_2.get_sub_1();
	const ParentExpr& new_sub_1_2    = is_first_sum ? comp_sub_1.get_sub_2() : comp_sub_2.get_sub_2();
	const CompExpr& new_mem_2  = is_first_sum ? comp_sub_2 : comp_sub_1;

	const ParentExpr& new_sub_1      = * new CompExpr{new_sub_1_1.clone(),new_mem_2.clone(),operation::mul}; // a * (c * d)
	const ParentExpr& new_sub_2      = * new CompExpr{new_sub_1_2.clone(),new_mem_2.clone(),operation::mul}; // b * (c * d)

	return * new CompExpr{new_sub_1,new_sub_2,operation::sum}; // (a * (c * d)) + (b * (c * d))
}
// ----------------------------------------------------------------------------------------------------------------------------------------
// Methods to obtain the expression in the form of sum of monomials

const CompExpr& CompExpr::stretch() const { // recursively calls stretch() to its sub expressions to distribute the sums. Then, it computes the operation to eventually distribute the result
	const ParentExpr& new_sub_1 = sub_1.stretch();
	const ParentExpr& new_sub_2 = sub_2.stretch();
	CompExpr new_comp{new_sub_1,new_sub_2,op};
	const CompExpr& c = new_comp.compute_operation();
	return c;
}
const CompExpr& CompExpr::extend() const { // calls stretch until the expression is in form of sum of monomials
	if(is_extended())
		return this->clone();
	const CompExpr& str = stretch();
	CompExpr tmp = str;
	delete &str;
	return tmp.extend();
}

const ParentExpr& CompExpr::unroll() const{ // from the vector of monomials that composes the expression, return an equivalent expression which is the sum of the monomials of vector
	std::vector<std::pair<int,std::map<Var,unsigned int>>> q = get_vector_of_monomials();
	const ParentExpr* polynomial = &create_monomial(q[0]); // the vector is for sure not empty (at least there is a constant)
	for(int i = 1; i < q.size(); i++)
		polynomial = new CompExpr{create_monomial(q[i]),*polynomial,operation::sum}; // sum the polynomial created so far with the i-th monomial
	return *polynomial;
}

const ParentExpr& ConstExpr::unroll() const { // it is trivial for a VarExpr
	return clone();
}

const ParentExpr& VarExpr::unroll() const { // it is trivial for a ConstExpr
	return clone();
}


bool CompExpr::is_extended() const { //check if the expression is in the form of sum of monomials
	bool is_comp_expr_1 = is_CompExpr(sub_1);
	bool is_comp_expr_2 = is_CompExpr(sub_2);

	if(!is_comp_expr_1 && !is_comp_expr_2) // if it is an operation between to simple expressions, then it is true
		return true;
	if(is_comp_expr_1 != is_comp_expr_2){ // if one is simple and another compound
		const CompExpr& comp_sub = is_comp_expr_1 ? dynamic_cast<const CompExpr&>(sub_1) : dynamic_cast<const CompExpr&>(sub_2);
		switch(op){
			case operation::sum:
				return comp_sub.is_extended(); // if the operation is a sum, then it is needed to check if the sub comp expression is a sum of monomials
			case operation::mul:
				return comp_sub.is_only_mult(); // if the operation is a multiplication, then it is needed to check if the sub comp expr is a monomial (only multiplications)
			default:
				return false;
		}
	}
	// At this point it is sure that the two sub expr are comp expr
	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);
	switch(op){
		case operation::sum: // if both are comp expr and the operation a sum, then it is needed to check that one comp expr is a monomial and the other a sum of monmials
			return (comp_sub_1.is_only_mult() && comp_sub_2.is_extended()) || (comp_sub_1.is_extended() && comp_sub_2.is_only_mult());
		case operation::mul: // if both are comp expr and the operation a multiplication, then it is needed to check that both are monomials
			return comp_sub_1.is_only_mult() && comp_sub_2.is_only_mult();
		default:
			return false;
	}
	
}

bool CompExpr::is_only_mult() const { // check that the comp expr is a monomial, i.e. all the sub operations are multiplications
	if(op == operation::sum)
		return false;
	bool is_sub_1_only_mult = true;
	bool is_sub_2_only_mult = true;
	if(is_CompExpr(sub_1))
		is_sub_1_only_mult = dynamic_cast<const CompExpr&>(sub_1).is_only_mult(); // check if the sub expr 1 is only made by multiplications
	if(is_CompExpr(sub_2))
		is_sub_2_only_mult = dynamic_cast<const CompExpr&>(sub_2).is_only_mult(); // check if the sub expr 2 is only made by multiplications
	
	return is_sub_1_only_mult && is_sub_2_only_mult;
}

const ParentExpr& CompExpr::ordered_monomial() const { // return a monomial which is ordered: first the constant part, then the power of the variables in alphanetic ordered
	if(!is_only_mult())
		throw NotMonomial{}; // Throw NotMonomial exception if this funciton is used with a non monomial expression
	return create_monomial(get_monomial());        // e.g.: ordered_monomial(x * z * 2 * y * x * x * 4) = 8 * x * x * x * y * z
}

std::pair<int,std::map<Var,unsigned int>> CompExpr::get_monomial() const{ // return the monomial in form of a std::pair<int,std::map<Var, unsigned int>>
	if(!is_only_mult())
		throw NotMonomial{}; // Throw NotMonomial exception if this funciton is used with a non monomial expression
	std::pair<int,std::map<Var,unsigned int>> monomial{};
	monomial.first = get_monomial_const();
	std::map<Var,unsigned int> degrees{};
	for(auto& v : vars) // extract the degree of every variable
		degrees.insert({v,get_degree(v)}); // insert into the map
	monomial.second = degrees;
	return monomial;
}

std::pair<int,std::map<Var,unsigned int>> VarExpr::get_monomial() const{ // return the variable in form of a std::pair
	std::map<Var,unsigned int> degree = {{vars[0],1}};
	std::pair<int,std::map<Var,unsigned int>> monomial{1,degree};
	return monomial;
}

std::pair<int,std::map<Var,unsigned int>> ConstExpr::get_monomial() const{ // return the constant in form of a std::pair
	std::map<Var,unsigned int> degree{};
	std::pair<int,std::map<Var,unsigned int>> monomial{value,degree};
	return monomial;
}

const ParentExpr& CompExpr::create_monomial(std::pair<int,std::map<Var,unsigned int>> monomial) { // creates an expression starting from a monomial in form of std::pair
	std::queue<const ParentExpr*> tmp_monomials{};
	for(auto& e : monomial.second) // for every variable with its degree
		tmp_monomials.push(&create_monomial(e.first, e.second)); // create a monomial with that variable and that degree and put it in a queue
	const ParentExpr* tmp_monomial = new ConstExpr{monomial.first};  // create the ConstExpr that will store the constant part
	if(monomial.first == 1 && !tmp_monomials.empty()){ // if the constant part is one and there are variables, omit the 1 in order not to have expressions like 1 * x * x * y
		delete tmp_monomial;
		tmp_monomial = tmp_monomials.front();
		tmp_monomials.pop();
	}
	while(!tmp_monomials.empty()){ // while there are monomial to mulitply in the queue
		tmp_monomial = new CompExpr{*tmp_monomial,*tmp_monomials.front(),operation::mul}; // multiply what we have so far with the new monomial
		tmp_monomials.pop(); // delete from queue
	}
	return *tmp_monomial;
}

std::vector<std::pair<int,std::map<Var,unsigned int>>> CompExpr::get_vector_of_monomials() const { // return the vector of monomials that composes an expression
	std::vector<std::pair<int,std::map<Var,unsigned int>>> vec{};
	const CompExpr& extended = dynamic_cast<const CompExpr&>(extend()); // extend the expression so to have it in the form of sum of monomials
	switch(extended.get_op()){
		case operation::mul:
			vec.push_back(extended.get_monomial()); // if the operation is a multiplication then the extended expression is a monomial and it is sufficient to put it in the vector
			break;
		case operation::sum:{ // if the operation is a sum, one sub expr is a monomial and the other a sum of monomials;
				      // it is thus needed to get the monomials of the rest of the expression and then add the other monomial
			const ParentExpr& ext_sub_1 = extended.get_sub_1();
			const ParentExpr& ext_sub_2 = extended.get_sub_2();
			bool is_only_mult_1 = ext_sub_1.is_only_mult();
			bool is_only_mult_2 = ext_sub_2.is_only_mult();

			if(is_only_mult_1 != is_only_mult_2){
				const ParentExpr& ext_sub = is_only_mult_1 ? ext_sub_2 : ext_sub_1; 
				vec = ext_sub.get_vector_of_monomials(); // get the monomials of the sub-sum
			}
			if(is_only_mult_1)
				ext_sub_1.insert_monomial(vec); // insert the monomial in the newly created vector
			if(is_only_mult_2)
				ext_sub_2.insert_monomial(vec);
			break;
		}
		default:
			break;
	}
	delete &extended; // the extended expression is no longer needed
	return vec;
}

void ParentExpr::insert_monomial(std::vector<std::pair<int,std::map<Var,unsigned int>>>& vec) const { // insert the monomial in an existing vector of monomials
	if(!is_only_mult())
		throw NotMonomial{}; // Throw NotMonomial exception if this funciton is used with a non monomial expression
	std::pair<int,std::map<Var,unsigned int>> monomial = get_monomial();
	for(auto& e : vec)
		if(e.second == monomial.second){ // if a monomial with the same degree already exists, sum the constant part of the two
			e.first += monomial.first;
			if(e.first == 0) // if the constant part now is 0, remove the monomial from the vector
				vec.erase(std::remove(vec.begin(),vec.end(),e),vec.end());
			return;
		}
	vec.push_back(monomial); // if it is not present just insert the monomial

}

std::vector<std::pair<int,std::map<Var,unsigned int>>> VarExpr::get_vector_of_monomials() const {// trivial if the expression is a VarExpr
	std::vector<std::pair<int,std::map<Var,unsigned int>>> q;
	q.push_back(get_monomial());
	return q;
}

std::vector<std::pair<int,std::map<Var,unsigned int>>> ConstExpr::get_vector_of_monomials() const {// trivial if the expression is a ConstExpr
	std::vector<std::pair<int,std::map<Var,unsigned int>>> q;
	q.push_back(get_monomial());
	return q;
}

int CompExpr:: get_monomial_const() const { // the costant part of a monomial is the multiplication of the constant part of the sub-monomias
	if(!is_only_mult())
		throw NotMonomial{}; // Throw NotMonomial exception if this funciton is used with a non monomial expression
	return sub_1.get_monomial_const() * sub_2.get_monomial_const();
} 
int VarExpr::  get_monomial_const() const { return 1; } // constant part of a VarExpr
int ConstExpr::get_monomial_const() const { return value;} // constant part of a ConstExpr is the value itself

// operators ---------------------------------------------------------------------------

const CompExpr& operator+ (const Var& v, int c){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new const CompExpr{*v_e,*c_e,operation::sum};
}

const CompExpr& operator+ (int c, const Var& v){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new const CompExpr{*c_e,*v_e,operation::sum};
}
const CompExpr& operator- (const Var& v, int c){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{-c};
	return * new const CompExpr{*v_e,*c_e,operation::sum};
}
const CompExpr& operator- (int c, const Var& v){
	ConstExpr* c_e 	     = new ConstExpr{c};
	return * new const CompExpr{*c_e,-v,operation::sum};
}
const CompExpr& operator* (const Var& v, int c){
	VarExpr* v_e   = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new const CompExpr{*v_e,*c_e,operation::mul};
}
const CompExpr& operator* (int c, const Var& v){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new const CompExpr{*c_e,*v_e,operation::mul};
}
const CompExpr& operator+ (const Var& v1, const Var& v2){
	const VarExpr* v_e_1 = new VarExpr{v1};
	const VarExpr* v_e_2 = new VarExpr{v2};
	return * new const CompExpr{*v_e_1,*v_e_2,operation::sum};
}
const CompExpr& operator- (const Var& v1, const Var& v2){
	VarExpr* v_e_1 	      = new VarExpr{v1};
	return * new const CompExpr{*v_e_1,-v2,operation::sum};
}
const CompExpr& operator* (const Var& v1, const Var& v2){
	VarExpr* v_e_1 = new VarExpr{v1};
	VarExpr* v_e_2 = new VarExpr{v2};
	return * new const CompExpr{*v_e_1,*v_e_2,operation::mul};
}

const CompExpr& operator- (const Var& v){
	ConstExpr* minus_one = new ConstExpr{-1};
	VarExpr* v_e = new VarExpr{v};
	std::string str = "-" + v.get_name();
	return * new const CompExpr{str,*minus_one,*v_e,operation::mul};
}

const CompExpr& operator+ (const CompExpr& e1, int i){
	ConstExpr* c_e = new ConstExpr{i};
	std::string str = "(" + e1.to_string() + ") + " + c_e->to_string();
	return * new const CompExpr{str,e1,*c_e,operation::sum};
}

const CompExpr& operator+(int i, const CompExpr& e1){
	ConstExpr* c_e = new ConstExpr{i};
	std::string str = c_e->to_string() + " + (" + e1.to_string() + ")";
	return * new const CompExpr{str,*c_e,e1,operation::sum};
}

const CompExpr& operator- (const CompExpr& e1, int i){
	ConstExpr* c_e = new ConstExpr{-i};
	std::string str = "(" + e1.to_string() + ") + " + c_e->to_string();
	return * new const CompExpr{str,e1,*c_e,operation::sum};
}

const CompExpr& operator-(int i, const CompExpr& e1){
	ConstExpr* c_e 	     = new ConstExpr{i};
	return * new const CompExpr{*c_e,-e1,operation::sum};
}

const CompExpr& operator* (const CompExpr& e1, int i){
	const ConstExpr* c_e = new ConstExpr{i};
	std::string str = "(" + e1.to_string() + ") * " + c_e->to_string();
	return * new const CompExpr{str,e1,*c_e,operation::mul};
}

const CompExpr& operator*(int i, const CompExpr& e1){
	ConstExpr* c_e = new ConstExpr{i};
	std::string str = c_e->to_string() + " * (" + e1.to_string() + ")";
	return * new const CompExpr{str,*c_e,e1,operation::mul};
}

const CompExpr& operator+ (const CompExpr& e1, const Var& v){
	VarExpr* v_e = new VarExpr{v};
	std::string str = "(" + e1.to_string() + ") + " + v.get_name();
	return * new const CompExpr{str,e1,*v_e,operation::sum};
}

const CompExpr& operator+(const Var& v, const CompExpr& e1){
	VarExpr* v_e = new VarExpr{v};
	std::string str = v.get_name() + " + (" + e1.to_string() + ")";
	return * new const CompExpr{str,*v_e,e1,operation::sum};
}

const CompExpr& operator- (const CompExpr& e1, const Var& v){
	std::string str = "(" + e1.to_string() + ") - " + v.get_name();
	return * new const CompExpr{str,e1,-v,operation::sum};
}

const CompExpr& operator-(const Var& v, const CompExpr& e1){
	VarExpr* v_e 	     = new VarExpr{v};
	std::string str = v.get_name() + " - (" + e1.to_string() + ")";
	return * new const CompExpr{str,*v_e,-e1,operation::sum};
}

const CompExpr& operator* (const CompExpr& e1, const Var& v){
	VarExpr* v_e = new VarExpr{v};
	std::string str = "(" + e1.to_string() + ") * " + v.get_name();
	return * new const CompExpr{str,e1,*v_e,operation::mul};
}

const CompExpr& operator*(const Var& v, const CompExpr& e1){
	VarExpr* v_e = new VarExpr{v};
	std::string str = v.get_name() + " * (" + e1.to_string() + ")";
	return * new const CompExpr{str,*v_e,e1,operation::mul};
}

const CompExpr& operator+(const CompExpr& e1, const CompExpr& e2){
	std::string str = "(" + e1.to_string() + ") + (" + e2.to_string() + ")"; 
	return * new const CompExpr{str,e1,e2,operation::sum};
}

const CompExpr& operator-(const CompExpr& e1, const CompExpr& e2){
	std::string str = "(" + e1.to_string() + ") - (" + e2.to_string() + ")"; 
	return * new const CompExpr{str,e1,-e2,operation::sum};
}

const CompExpr& operator*(const CompExpr& e1, const CompExpr& e2){
	std::string str = "(" + e1.to_string() + ") * (" + e2.to_string() + ")"; 
	return * new const CompExpr{str,e1,e2,operation::mul};
}

const CompExpr& operator-(const CompExpr& e1){
	ConstExpr* minus_one = new ConstExpr{-1};
	std::string str = "-(" + e1.to_string() + ")";
	return * new const CompExpr{str,*minus_one,e1,operation::mul};
}
