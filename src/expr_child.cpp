#include "expr_child.h"
#include "expr_parent.h"
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

VarExpr::VarExpr(const Var& v):
	ParentExpr(v.get_name(),{v}){}

void VarExpr::set_value(int v){
	vars[0].set_value(v);
}

int VarExpr::evaluate(){
	return vars[0].get_value();
}

const VarExpr& VarExpr::stretch() const {
	return * new VarExpr{*this};
}

const VarExpr& VarExpr::extend() const {
	return *this; 
}

const VarExpr& VarExpr::clone() const{
	return * new VarExpr{*this};
}

bool VarExpr::is_only_mult() const{
	return true;
}

int VarExpr::get_degree(const Var& v) const{
	//return v.get_name().compare(vars[0].get_name()) == 0 ? 1 : 0;
	return v == vars[0] ? 1 : 0;
}

VarExpr::~VarExpr() = default;

bool VarExpr::is_extended() const {
	return true;
}

std::map<unsigned int, const ParentExpr*> VarExpr::get_coeffs(const Var& v) const {
	std::map<unsigned int,const ParentExpr*> coeffs{};
	bool is_same_var = v == vars[0];// vars[0].get_name().compare(v.get_name()) == 0;
	if(is_same_var){
		ConstExpr* g_1 = new ConstExpr{1};
		coeffs.insert({1,g_1});
	}
	return coeffs;
}

void VarExpr::insert_coeff(std::map<unsigned int, const ParentExpr*>& coeffs, const Var& v) const{
	bool is_same_var = vars[0] == v;//to_string().compare(v.get_name()) == 0;
	int degree       = is_same_var ? 1 : 0;
	std::map<unsigned int, const ParentExpr*>::iterator present = coeffs.find(degree);
	const ParentExpr* new_sub;
	if(is_same_var)
		new_sub = new ConstExpr{1};
	else{
		new_sub = &clone();
	}
	if(present != coeffs.end()){
		const ParentExpr* new_coeff = new CompExpr{*coeffs[degree],*new_sub,operation::sum};
		present->second = new_coeff;
	}
	else{
		coeffs.insert({degree,new_sub});
	}
}

const ParentExpr& VarExpr::extract_monomial(const Var& v) const {
	//if(to_string().compare(v.get_name()) == 0)
	if(vars[0] == v)
		return * new ConstExpr{1};
	return this->clone();
}

const ParentExpr& VarExpr::replace(const std::map<Var,const ParentExpr*>& repl) const {
	bool present = repl.find(vars[0]) != repl.end();
	if(!present)
		return this->clone();
	return repl.at(vars[0])->clone();
}

bool VarExpr::is_VarExpr(const ParentExpr& ex){ return dynamic_cast<const VarExpr*>(&ex); }

ConstExpr::ConstExpr(const int i):
	value{i},ParentExpr(std::to_string(i)){}

int ConstExpr::evaluate(){
	return value;
}

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


std::map<unsigned int, const ParentExpr*> ConstExpr::get_coeffs(const Var& v) const {
	return std::map<unsigned int, const ParentExpr*>{};
}

void ConstExpr::insert_coeff(std::map<unsigned int, const ParentExpr*>& coeffs, const Var& v) const{
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

std::string CompExpr::create_string(const ParentExpr& e1, const ParentExpr& e2, const operation op){
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

CompExpr::CompExpr(const std::string& expr, const ParentExpr& e1, const ParentExpr& e2, operation op):
	sub_1{e1},sub_2{e2},op{op},ParentExpr(expr)
	{}

CompExpr::CompExpr(const std::string& expr, const std::vector<Var>& vars, const ParentExpr& e1, const ParentExpr& e2, operation op):
	sub_1{e1},sub_2{e2},op{op},ParentExpr(expr,vars)
	{}

CompExpr::CompExpr(const CompExpr& comp):
	sub_1{comp.get_sub_1().clone()},sub_2{comp.get_sub_2().clone()},op{comp.get_op()},ParentExpr(comp){}


const ParentExpr& CompExpr::create_monomial(const Var& v, unsigned int degree) {
	if(degree == 0)
		return * new ConstExpr{1};
	const VarExpr& var = * new VarExpr{v};
	if(degree == 1)
		return var;
	return * new CompExpr{var,create_monomial(v,degree - 1),operation::mul};
};

const operation CompExpr::get_op() const { return op; }

const ParentExpr& CompExpr::get_sub_1() const { return sub_1; }
const ParentExpr& CompExpr::get_sub_2() const { return sub_2; }

const CompExpr& CompExpr::clone() const{
	const ParentExpr& clone_sub_1 = sub_1.clone();
	const ParentExpr& clone_sub_2 = sub_2.clone();
	return * new CompExpr{clone_sub_1,clone_sub_2,op};
}

std::map<unsigned int, const ParentExpr*> CompExpr::get_coeffs(const Var& v) const {
	std::map<unsigned int,const ParentExpr*> coeffs{};
	const CompExpr& extended = dynamic_cast<const CompExpr&>(extend());
	switch(extended.get_op()){
		case operation::mul:
			extended.insert_coeff(coeffs,v);
			break;
		case operation::sum:{
			const ParentExpr& ext_sub_1 = extended.get_sub_1();
			const ParentExpr& ext_sub_2 = extended.get_sub_2();
			bool is_only_mult_1 = ext_sub_1.is_only_mult();
			bool is_only_mult_2 = ext_sub_2.is_only_mult();

			if(is_only_mult_1 != is_only_mult_2){
				const ParentExpr& ext_sub = is_only_mult_1 ? ext_sub_2 : ext_sub_1; 
				coeffs = ext_sub.get_coeffs(v);
			}
	
			if(is_only_mult_1)
				ext_sub_1.insert_coeff(coeffs,v);
			if(is_only_mult_2)
				ext_sub_2.insert_coeff(coeffs,v);
			break;
		}
		default:
			break;
	}
	delete &extended;
	return coeffs;
}

void CompExpr::insert_coeff(std::map<unsigned int, const ParentExpr*>& coeffs, const Var &v) const {
	int degree = get_degree(v);
	const ParentExpr& new_monomial = extract_monomial(v);
	std::map<unsigned int,const ParentExpr*>::iterator present = coeffs.find(degree);
	const ParentExpr* new_coeff = &new_monomial;
	if(present != coeffs.end()){
		new_coeff = new CompExpr{*coeffs[degree],new_monomial,operation::sum};
		present->second = new_coeff;
	}
	coeffs.insert({degree,new_coeff});
}

int CompExpr::get_degree(const Var& v) const {
	return sub_1.get_degree(v) + sub_2.get_degree(v);	
}

const ParentExpr& CompExpr::extract_monomial(const Var& v) const {
	bool is_var_1 = dynamic_cast<const VarExpr*>(&sub_1);
	bool is_var_2 = dynamic_cast<const VarExpr*>(&sub_2);
	if(is_var_1 || is_var_2){
		const VarExpr& var = is_var_1 ? dynamic_cast<const VarExpr&>(sub_1) : dynamic_cast<const VarExpr&>(sub_2);
		const ParentExpr& other_sub = is_var_1 ? sub_2 : sub_1;
		if(var.get_variables()[0] == v)//if(var.to_string().compare(v.get_name()) == 0)
			return other_sub.extract_monomial(v);
		return * new CompExpr{var.clone(),other_sub.extract_monomial(v),operation::mul};
	
	}
	return * new CompExpr{sub_1.extract_monomial(v),sub_2.extract_monomial(v),operation::mul};
}

const ParentExpr& CompExpr::replace(const std::map<Var,const ParentExpr*>& repl) const {
	const ParentExpr& new_sub_1 = sub_1.replace(repl);
	const ParentExpr& new_sub_2 = sub_2.replace(repl);
	bool is_comp_expr_1 = is_CompExpr(new_sub_1);
	bool is_comp_expr_2 = is_CompExpr(new_sub_2);
	std::string str_1 = is_comp_expr_1 ? "(" + new_sub_1.to_string() + ") " : new_sub_1.to_string() + " ";
	std::string str_2 = is_comp_expr_2 ? " (" + new_sub_2.to_string() + ")" : " " + new_sub_2.to_string();
	char op_c = get_op() == operation::sum ? '+' : '*';
	std::string str = str_1 + op_c + str_2; 
	return * new CompExpr{str,new_sub_1,new_sub_2,get_op()};
}

const CompExpr& CompExpr::compute_operation(){
	
	bool is_comp_expr_1 = is_CompExpr(sub_1);	// wether the first sub-expression is simple or compound
	bool is_comp_expr_2 = is_CompExpr(sub_2);	// idem for the second sub-expr
	
	if(!is_comp_expr_1 && !is_comp_expr_2)// return a copy of the expression if the sub-expressions are simple	
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

const CompExpr& CompExpr::sum_simple_comp(){
	bool is_comp_expr_1 = is_CompExpr(sub_1);
	const CompExpr& sub_comp = is_comp_expr_1 ? dynamic_cast<const CompExpr&>(sub_1) : dynamic_cast<const CompExpr&>(sub_2);
	const ParentExpr& sub    = is_comp_expr_1 ? sub_2 : sub_1;
	return * new CompExpr{sub.clone(),sub_comp.clone(),operation::sum};
}

const CompExpr& CompExpr::compound_sum(){
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

const CompExpr& CompExpr::sum_sum(){
	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);

	const CompExpr& sum_2 = * new CompExpr{comp_sub_1.get_sub_2().clone(),comp_sub_2.clone(),operation::sum};

	const CompExpr& sum_1 = * new CompExpr{comp_sub_1.get_sub_1().clone(),sum_2,operation::sum};

	return sum_1;
}

const CompExpr& CompExpr::sum_mult(){
	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);
	return * new CompExpr{comp_sub_1.clone(),comp_sub_2.clone(),operation::sum};
}

const CompExpr& CompExpr::sum_mixed(){
	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);
	bool is_first_sum = comp_sub_1.get_op() == operation::sum;

	const ParentExpr& new_sub_1_1 = is_first_sum ? comp_sub_1.get_sub_1() : comp_sub_2.get_sub_1();
	const ParentExpr& new_sub_1_2 = is_first_sum ? comp_sub_1.get_sub_2() : comp_sub_2.get_sub_2();
	const CompExpr& new_mem_2    = is_first_sum ? comp_sub_2 : comp_sub_1;

	const ParentExpr& sum_2 = * new CompExpr{new_sub_1_2.clone(),new_mem_2.clone(),operation::sum};

	return * new CompExpr{new_sub_1_1.clone(),sum_2,operation::sum};
}

const CompExpr& CompExpr::mult_simple_comp(){
	bool is_comp_expr_1 = is_CompExpr(sub_1);
	const CompExpr& sub_comp = is_comp_expr_1 ? dynamic_cast<const CompExpr&>(sub_1) : dynamic_cast<const CompExpr&>(sub_2);
	const ParentExpr& sub_simple   = is_comp_expr_1 ? sub_2 : sub_1;
	operation sub_op   = sub_comp.get_op();
	switch(sub_op){
		case operation::sum:
			return this->distr_law();
		case operation::mul:{
			std::string mem2 = sub_comp.to_string();
			//std::string mul = sub_simple.to_string() + " * " + sub_comp.to_string();
			return * new CompExpr{sub_simple.clone(),sub_comp.clone(),op};
		    }
		default:
			return this->clone();
	}
}

const CompExpr& CompExpr::distr_law(){
	bool is_comp_expr_1 = is_CompExpr(sub_1);
	const CompExpr& comp_sub = is_comp_expr_1 ? dynamic_cast<const CompExpr&>(sub_1) : dynamic_cast<const CompExpr&>(sub_2);
	const ParentExpr& simple_sub = is_comp_expr_1 ? sub_2 : sub_1;

	const ParentExpr& new_sub_1 = * new CompExpr{simple_sub.clone(),comp_sub.get_sub_1().clone(),operation::mul};
	const ParentExpr& new_sub_2 = * new CompExpr{simple_sub.clone(),comp_sub.get_sub_2().clone(),operation::mul};

	return * new CompExpr{new_sub_1,new_sub_2,operation::sum};
}

const CompExpr& CompExpr::compound_mult(){
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

const CompExpr& CompExpr::mult_sum(){

	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);

	const CompExpr&   mul_1_1   = * new CompExpr{comp_sub_1.get_sub_1().clone(),comp_sub_2.get_sub_1().clone(),operation::mul};
	const CompExpr&   mul_1_2   = * new CompExpr{comp_sub_1.get_sub_1().clone(),comp_sub_2.get_sub_2().clone(),operation::mul};
		
	const CompExpr&   mul_2_1   = * new CompExpr{comp_sub_1.get_sub_2().clone(),comp_sub_2.get_sub_1().clone(),operation::mul};
	const CompExpr&   mul_2_2   = * new CompExpr{comp_sub_1.get_sub_2().clone(),comp_sub_2.get_sub_2().clone(),operation::mul};
		
	const CompExpr&     sum_3   = * new CompExpr{mul_2_1,mul_2_2,operation::sum};
	const CompExpr&     sum_2   = * new CompExpr{mul_1_2,sum_3,operation::sum};
	const CompExpr&     sum_1   = * new CompExpr{mul_1_1,sum_2,operation::sum};

	return sum_1;
}

const CompExpr& CompExpr::mult_mult(){
	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);

	const CompExpr& mul_2 = * new CompExpr{comp_sub_1.get_sub_2().clone(),comp_sub_2.clone(),operation::mul};

	const CompExpr& mul_1 = * new CompExpr{comp_sub_1.get_sub_1().clone(),mul_2,operation::mul};

	return mul_1;
}

const CompExpr& CompExpr::mult_mixed(){
	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);
	bool is_first_sum    = comp_sub_1.get_op() == operation::sum;

	const ParentExpr& new_sub_1_1    = is_first_sum ? comp_sub_1.get_sub_1() : comp_sub_2.get_sub_1();
	const ParentExpr& new_sub_1_2    = is_first_sum ? comp_sub_1.get_sub_2() : comp_sub_2.get_sub_2();
	const CompExpr& new_mem_2  = is_first_sum ? comp_sub_2 : comp_sub_1;

	const ParentExpr& new_sub_1      = * new CompExpr{new_sub_1_1.clone(),new_mem_2.clone(),operation::mul};

	const ParentExpr& new_sub_2      = * new CompExpr{new_sub_1_2.clone(),new_mem_2.clone(),operation::mul};

	return * new CompExpr{new_sub_1,new_sub_2,operation::sum};
}

const CompExpr& CompExpr::stretch() const {
	const ParentExpr& new_sub_1 = sub_1.stretch();
	const ParentExpr& new_sub_2 = sub_2.stretch();
	CompExpr new_comp{new_sub_1,new_sub_2,op};
	const CompExpr& c = new_comp.compute_operation();
	return c;
}
const CompExpr& CompExpr::extend() const {
	if(is_extended())
		return this->clone();
	const CompExpr& str = stretch();
	CompExpr tmp = str;
	delete &str;
	return tmp.extend();
}

bool CompExpr::is_extended() const {
	bool is_comp_expr_1 = is_CompExpr(sub_1);
	bool is_comp_expr_2 = is_CompExpr(sub_2);

	if(!is_comp_expr_1 && !is_comp_expr_2)
		return true;
	if(is_comp_expr_1 != is_comp_expr_2){
		const CompExpr& comp_sub = is_comp_expr_1 ? dynamic_cast<const CompExpr&>(sub_1) : dynamic_cast<const CompExpr&>(sub_2);
		switch(op){
			case operation::sum:
				return comp_sub.is_extended();
			case operation::mul:
				return comp_sub.is_only_mult();
			default:
				return false;
		}
	}

	const CompExpr& comp_sub_1 = dynamic_cast<const CompExpr&>(sub_1);
	const CompExpr& comp_sub_2 = dynamic_cast<const CompExpr&>(sub_2);
	switch(op){
		case operation::sum:
			return (comp_sub_1.is_only_mult() && comp_sub_2.is_extended()) || (comp_sub_1.is_extended() && comp_sub_2.is_only_mult());
		case operation::mul:
			return comp_sub_1.is_only_mult() && comp_sub_2.is_only_mult();
		default:
			return false;
	}
	
}

bool CompExpr::is_only_mult() const {
	if(op == operation::sum)
		return false;
	bool is_sub_1_only_mult = true;
	bool is_sub_2_only_mult = true;
	if(is_CompExpr(sub_1))
		is_sub_1_only_mult = dynamic_cast<const CompExpr&>(sub_1).is_only_mult();
	if(is_CompExpr(sub_2))
		is_sub_2_only_mult = dynamic_cast<const CompExpr&>(sub_2).is_only_mult();
	
	return is_sub_1_only_mult && is_sub_2_only_mult;
}

int CompExpr::evaluate(){
	return 0;
}

CompExpr::~CompExpr(){
	delete &sub_1;
	delete &sub_2;
}

bool are_same_type(const ParentExpr& e1, const ParentExpr& e2){
	return (VarExpr::is_VarExpr(e1) && VarExpr::is_VarExpr(e2)) || 
	       (ConstExpr::is_ConstExpr(e1) && ConstExpr::is_ConstExpr(e2)) ||
	       (CompExpr::is_CompExpr(e1) && CompExpr::is_CompExpr(e2));
}

bool are_equal(const ParentExpr& e1, const ParentExpr& e2){
	if(!are_same_type(e1,e2))
		return false;

}

const ParentExpr& CompExpr::extend_and_group() const {
	const CompExpr& extended = dynamic_cast<const CompExpr&>(extend());
	if(extended.get_op() == operation::mul)
		return ordered_monomial();
	return * new CompExpr{extended.get_sub_1().extend_and_group(),extended.get_sub_2().extend_and_group(),operation::sum};
}

const ParentExpr& VarExpr:: extend_and_group() const {
	return clone();
}

const ParentExpr& ConstExpr:: extend_and_group() const {
	return clone();
}

const ParentExpr& CompExpr::ordered_monomial() const {
	return create_monomial(get_monomial());
}

std::pair<int,std::map<Var,unsigned int>> CompExpr::get_monomial() const{
	std::pair<int,std::map<Var,unsigned int>> monomial{};
	monomial.first = get_monomial_const();
	std::map<Var,unsigned int> degrees{};
	for(auto& v : vars)
		degrees.insert({v,get_degree(v)});
	monomial.second = degrees;
	return monomial;
}

std::pair<int,std::map<Var,unsigned int>> VarExpr::get_monomial() const{
	std::map<Var,unsigned int> degree = {{vars[0],1}};
	std::pair<int,std::map<Var,unsigned int>> monomial{1,degree};
	return monomial;
}

std::pair<int,std::map<Var,unsigned int>> ConstExpr::get_monomial() const{
	std::map<Var,unsigned int> degree{};
	std::pair<int,std::map<Var,unsigned int>> monomial{value,degree};
	return monomial;
}

const ParentExpr& CompExpr::create_monomial(std::pair<int,std::map<Var,unsigned int>> monomial) {
	std::queue<const ParentExpr*> tmp_monomials{};
	for(auto& e : monomial.second)
		tmp_monomials.push(&create_monomial(e.first, e.second));
	const ParentExpr* tmp_monomial = new ConstExpr{monomial.first};
	if(monomial.first == 1 && !tmp_monomials.empty()){
		delete tmp_monomial;
		tmp_monomial = tmp_monomials.front();
		tmp_monomials.pop();
	}
	while(!tmp_monomials.empty()){
		tmp_monomial = new CompExpr{*tmp_monomial,*tmp_monomials.front(),operation::mul};
		tmp_monomials.pop();
	}
	return *tmp_monomial;
}

std::vector<std::pair<int,std::map<Var,unsigned int>>> CompExpr::get_vector_of_monomials() const {
	std::vector<std::pair<int,std::map<Var,unsigned int>>> vec{};
	const CompExpr& extended = dynamic_cast<const CompExpr&>(extend());
	switch(extended.get_op()){
		case operation::mul:
			vec.push_back(extended.get_monomial());
			break;
		case operation::sum:{
			const ParentExpr& ext_sub_1 = extended.get_sub_1();
			const ParentExpr& ext_sub_2 = extended.get_sub_2();
			bool is_only_mult_1 = ext_sub_1.is_only_mult();
			bool is_only_mult_2 = ext_sub_2.is_only_mult();

			if(is_only_mult_1 != is_only_mult_2){
				const ParentExpr& ext_sub = is_only_mult_1 ? ext_sub_2 : ext_sub_1; 
				vec = ext_sub.get_vector_of_monomials();
			}
			if(is_only_mult_1)
				ext_sub_1.insert_monomial(vec);
			if(is_only_mult_2)
				ext_sub_2.insert_monomial(vec);
			break;
		}
		default:
			break;
	}
	delete &extended;
	return vec;
}

void ParentExpr::insert_monomial(std::vector<std::pair<int,std::map<Var,unsigned int>>>& vec) const {
	std::pair<int,std::map<Var,unsigned int>> monomial = get_monomial();
	for(auto& e : vec)
		if(e.second == monomial.second){
			e.first += monomial.first;
			return;
		}
	vec.push_back(monomial);

}

std::vector<std::pair<int,std::map<Var,unsigned int>>> VarExpr::get_vector_of_monomials() const {
	std::vector<std::pair<int,std::map<Var,unsigned int>>> q;
	q.push_back(get_monomial());
	return q;
}

std::vector<std::pair<int,std::map<Var,unsigned int>>> ConstExpr::get_vector_of_monomials() const {
	std::vector<std::pair<int,std::map<Var,unsigned int>>> q;
	q.push_back(get_monomial());
	return q;
}

int CompExpr:: get_monomial_const() const { return sub_1.get_monomial_const() * sub_2.get_monomial_const();}
int VarExpr::  get_monomial_const() const { return 1; }
int ConstExpr::get_monomial_const() const { return value;}

const ParentExpr& CompExpr::unroll() const{
	std::vector<std::pair<int,std::map<Var,unsigned int>>> q = get_vector_of_monomials();
	const ParentExpr* polynomial = &create_monomial(q[0]);
	for(int i = 1; i < q.size(); i++)
		polynomial = new CompExpr{create_monomial(q[i]),*polynomial,operation::sum};
	return *polynomial;
}

const ParentExpr& ConstExpr::unroll() const {
	return clone();
}

const ParentExpr& VarExpr::unroll() const {
	return clone();
}

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
	ConstExpr* c_e = new ConstExpr{c};
	return * new const CompExpr{*v_e,*c_e,operation::sub};
}
const CompExpr& operator- (int c, const Var& v){
	VarExpr* v_e   = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new const CompExpr{*c_e,*v_e,operation::sub};
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
	VarExpr* v_e_1 = new VarExpr{v1};
	VarExpr* v_e_2 = new VarExpr{v2};
	return * new const CompExpr{*v_e_1,*v_e_2,operation::sub};
}
const CompExpr& operator* (const Var& v1, const Var& v2){
	VarExpr* v_e_1 = new VarExpr{v1};
	VarExpr* v_e_2 = new VarExpr{v2};
	return * new const CompExpr{*v_e_1,*v_e_2,operation::mul};
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
	ConstExpr* c_e = new ConstExpr{i};
	std::string str = "(" + e1.to_string() + ") - " + c_e->to_string();
	return * new const CompExpr{str,e1,*c_e,operation::sub};
}

const CompExpr& operator-(int i, const CompExpr& e1){
	ConstExpr* c_e = new ConstExpr{i};
	std::string str = c_e->to_string() + " -(" + e1.to_string() + ")";
	return * new const CompExpr{str,*c_e,e1,operation::sub};
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
	VarExpr* v_e = new VarExpr{v};
	std::string str = "(" + e1.to_string() + ") - " + v.get_name();
	return * new const CompExpr{str,e1,*v_e,operation::sub};
}

const CompExpr& operator-(const Var& v, const CompExpr& e1){
	VarExpr* v_e = new VarExpr{v};
	std::string str = v.get_name() + " - (" + e1.to_string() + ")";
	return * new const CompExpr{str,*v_e,e1,operation::sub};
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
	return * new const CompExpr{str,e1,e2,operation::sub};
}

const CompExpr& operator*(const CompExpr& e1, const CompExpr& e2){
	std::string str = "(" + e1.to_string() + ") * (" + e2.to_string() + ")"; 
	return * new const CompExpr{str,e1,e2,operation::mul};
}
