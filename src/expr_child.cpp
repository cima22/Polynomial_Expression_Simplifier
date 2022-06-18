#include "expr_child.h"
#include <string>
#include <type_traits>

VarExpr::VarExpr(const Var& v):
	Expr(v.get_name(),{v}){}

void VarExpr::set_value(int v){
	vars[0].set_value(v);
}

int VarExpr::evaluate(){
	return vars[0].get_value();
}

VarExpr& VarExpr::stretch(){
	return *this;
}

VarExpr& VarExpr::extend(){
	return *this;
}

bool VarExpr::is_extended(){
	return true;
}

std::map<unsigned int, ParentExpr> VarExpr::get_coeffs(const Var& v){
	std::map coeffs<unsigned int, Expr>;
	bool is_same_var = vars[0].get_name().compare(v.get_name())
	ConsExpr g_1 = is_same_var ? ConstExpr{1} : ConstExpr{0};
	ConsExpr g_0{0};
	coeffs.insert({0,g_0});
	coeffs.insert({1,g_1});
	return coeffs;
}

ConstExpr::ConstExpr(const int i):
	value{i},Expr(std::to_string(i)){}

int ConstExpr::evaluate(){
	return value;
}

ConstExpr& ConstExpr::stretch(){
	return *this;
}

ConstExpr& ConstExpr::extend(){
	return *this;
}

bool ConstExpr::is_extended(){
	return true;
}

std::map<unsigned int, ConstExpr> ConstExpr::get_coeffs(const Var& v){
	return std::map<unsigned int, ConstExpr>{{0,ConstExpr{0}}};
}

std::string CompExpr::create_string(ParentExpr& e1, ParentExpr& e2, const operation op){
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
	
	std::string member_1 = e1.to_string();
	std::string member_2 = e2.to_string();
	if(dynamic_cast<CompExpr*>(&e1))
		member_1 = "(" + e1.to_string() + ")";
	if(dynamic_cast<CompExpr*>(&e2))
		member_2 = "(" + e2.to_string() + ")";

	return std::string{member_1 + " " + op_c + " " + member_2};
}

bool CompExpr::is_CompExpr(ParentExpr& ex){ return dynamic_cast<CompExpr*>(&ex); }

CompExpr::CompExpr(ParentExpr& e1, ParentExpr& e2, const operation op):
	sub_1{e1}, sub_2{e2}, op{op}, Expr(create_string(e1,e2,op))
	{}

CompExpr::CompExpr(const std::string& expr, ParentExpr& e1, ParentExpr& e2, operation op):
	sub_1{e1},sub_2{e2},op{op},Expr(expr)
	{}

CompExpr::CompExpr(const std::string& expr, const std::vector<Var>& vars, ParentExpr& e1, ParentExpr& e2, operation op):
	sub_1{e1},sub_2{e2},op{op},Expr(expr,vars)
	{}

operation CompExpr::get_op(){ return op; }

Expr& CompExpr::get_sub_1(){ return sub_1; }
Expr& CompExpr::get_sub_2(){ return sub_2; }

CompExpr& CompExpr::compute_operation(){
	
	bool is_comp_expr_1 = is_CompExpr(sub_1);	// wether the first sub-expression is simple or compound
	bool is_comp_expr_2 = is_CompExpr(sub_2);	// idem for the second sub-expr
	
	if(!is_comp_expr_1 && !is_comp_expr_2)		// return a copy of the expression if the sub-expressions are simple
		return * new CompExpr{sub_1,sub_2,op};
	
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

CompExpr& CompExpr::sum_simple_comp(){
	bool is_comp_expr_1 = is_CompExpr(sub_1);
	CompExpr& sub_comp = is_comp_expr_1 ? dynamic_cast<CompExpr&>(sub_1) : dynamic_cast<CompExpr&>(sub_2);
	Expr& sub          = is_comp_expr_1 ? sub_2 : sub_1;
	std::string sum = sub.to_string() + " + " + sub_comp.to_string();
	return * new CompExpr{sum,sub,sub_comp,operation::sum};
}

CompExpr& CompExpr::compound_sum(){
	CompExpr& comp_sub_1 = dynamic_cast<CompExpr&>(sub_1);
	operation op_sub_1   = comp_sub_1.get_op();
	CompExpr& comp_sub_2 = dynamic_cast<CompExpr&>(sub_2);
	operation op_sub_2   = comp_sub_2.get_op();

	if(op_sub_1 == operation::sum && op_sub_2 == operation::sum)
		return this->sum_sum();
	if(op_sub_1 == operation::mul && op_sub_2 == operation::mul)
		return this->sum_mult();
	return this->sum_mixed();
}

CompExpr& CompExpr::sum_sum(){
	CompExpr& comp_sub_1 = dynamic_cast<CompExpr&>(sub_1);
	CompExpr& comp_sub_2 = dynamic_cast<CompExpr&>(sub_2);

	std::string str_2 = comp_sub_1.get_sub_2().to_string() + " + " + comp_sub_2.to_string();
	CompExpr& sum_2 = * new CompExpr{str_2,comp_sub_1.get_sub_2(),comp_sub_2,operation::sum};

	std::string str_1 = comp_sub_1.get_sub_1().to_string() + " + " + sum_2.to_string();
	CompExpr& sum_1 = * new CompExpr{comp_sub_1.get_sub_1(),sum_2,operation::sum};

	return sum_1;
}

CompExpr& CompExpr::sum_mult(){
	CompExpr& comp_sub_1 = dynamic_cast<CompExpr&>(sub_1);
	CompExpr& comp_sub_2 = dynamic_cast<CompExpr&>(sub_2);
	std::string str = comp_sub_1.to_string() + " + " + comp_sub_2.to_string();
	return * new CompExpr{str,comp_sub_1,comp_sub_2,operation::sum};
}

CompExpr& CompExpr::sum_mixed(){
	CompExpr& comp_sub_1 = dynamic_cast<CompExpr&>(sub_1);
	CompExpr& comp_sub_2 = dynamic_cast<CompExpr&>(sub_2);

	bool is_first_sum = comp_sub_1.get_op() == operation::sum;
	Expr& new_sub_1_1 = is_first_sum ? comp_sub_1.get_sub_1() : comp_sub_2.get_sub_1();
	Expr& new_sub_1_2 = is_first_sum ? comp_sub_1.get_sub_2() : comp_sub_2.get_sub_2();
	CompExpr& new_mem_2    = is_first_sum ? comp_sub_2 : comp_sub_1;

	std::string str_2 = new_sub_1_2.to_string() + " + " + new_mem_2.to_string();
	Expr& sum_2 = * new CompExpr{str_2,new_sub_1_2,new_mem_2,operation::sum};

	std::string str = new_sub_1_1.to_string() + " + " + sum_2.to_string();
	return * new CompExpr{str,new_sub_1_1,sum_2,operation::sum};
}

CompExpr& CompExpr::mult_simple_comp(){
	bool is_comp_expr_1 = is_CompExpr(sub_1);
	CompExpr& sub_comp = is_comp_expr_1 ? dynamic_cast<CompExpr&>(sub_1) : dynamic_cast<CompExpr&>(sub_2);
	Expr& sub_simple   = is_comp_expr_1 ? sub_2 : sub_1;
	operation sub_op   = sub_comp.get_op();
	switch(sub_op){
		case operation::sum:
			return this->distr_law();
		case operation::mul:{
			std::string mem2 = sub_comp.to_string();
			std::string mul = sub_simple.to_string() + " * " + sub_comp.to_string();
			return * new CompExpr{mul,this->vars,sub_simple,sub_comp,op};
		    }
		default:
			return *this;
	}

}

CompExpr& CompExpr::distr_law(){
	bool is_comp_expr_1 = is_CompExpr(sub_1);
	CompExpr& comp_sub = is_comp_expr_1 ? dynamic_cast<CompExpr&>(sub_1) : dynamic_cast<CompExpr&>(sub_2);
	Expr& simple_sub = is_comp_expr_1 ? sub_2 : sub_1;

	std::string mul_1 = simple_sub.to_string() + " * " + comp_sub.get_sub_1().to_string();
	Expr& new_sub_1 = * new CompExpr{mul_1,simple_sub,comp_sub.get_sub_1(),operation::mul};

	std::string mul_2 = simple_sub.to_string() + " * " + comp_sub.get_sub_2().to_string();
	Expr& new_sub_2 = * new CompExpr{mul_2,simple_sub,comp_sub.get_sub_2(),operation::mul};

	std::string sum = mul_1 + " + " + mul_2;
	return * new CompExpr{sum,new_sub_1,new_sub_2,operation::sum};
}

CompExpr& CompExpr::compound_mult(){
	CompExpr& comp_sub_1 = dynamic_cast<CompExpr&>(sub_1);
	operation op_sub_1   = comp_sub_1.get_op();
	CompExpr& comp_sub_2 = dynamic_cast<CompExpr&>(sub_2);
	operation op_sub_2   = comp_sub_2.get_op();

	if(op_sub_1 == operation::sum && op_sub_2 == operation::sum)
		return this->mult_sum();
	if(op_sub_1 == operation::mul && op_sub_2 == operation::mul)
		return this->mult_mult();
	return this->mult_mixed();
}

CompExpr& CompExpr::mult_sum(){

	CompExpr& comp_sub_1 = dynamic_cast<CompExpr&>(sub_1);
	CompExpr& comp_sub_2 = dynamic_cast<CompExpr&>(sub_2);

	std::string str_1_1   = comp_sub_1.get_sub_1().to_string() + " * " + comp_sub_2.get_sub_1().to_string();
	CompExpr&   mul_1_1   = * new CompExpr{str_1_1,comp_sub_1.get_sub_1(),comp_sub_2.get_sub_1(),operation::mul};

	std::string str_1_2   = comp_sub_1.get_sub_1().to_string() + " * " + comp_sub_2.get_sub_2().to_string();
	CompExpr&   mul_1_2   = * new CompExpr{str_1_2,comp_sub_1.get_sub_1(),comp_sub_2.get_sub_2(),operation::mul};
		
	std::string str_2_1   = comp_sub_1.get_sub_2().to_string() + " * " + comp_sub_2.get_sub_1().to_string();
	CompExpr&   mul_2_1   = * new CompExpr{str_2_1,comp_sub_1.get_sub_2(),comp_sub_2.get_sub_1(),operation::mul};
		
	std::string str_2_2   = comp_sub_1.get_sub_2().to_string() + " * " + comp_sub_2.get_sub_2().to_string();
	CompExpr&   mul_2_2   = * new CompExpr{str_2_2,comp_sub_1.get_sub_2(),comp_sub_2.get_sub_2(),operation::mul};
		
	std::string   str_3   = mul_2_1.to_string() + " + " + mul_2_2.to_string();
	CompExpr&     sum_3   = * new CompExpr{str_3,mul_2_1,mul_2_2,operation::sum};
		
	std::string   str_2   = mul_1_2.to_string() + " + " + sum_3.to_string();
	CompExpr&     sum_2   = * new CompExpr{str_2,mul_1_2,sum_3,operation::sum};

	std::string   str_1   = mul_1_1.to_string() + " + " + sum_2.to_string();
	CompExpr&     sum_1   = * new CompExpr{str_1,mul_1_1,sum_2,operation::sum};

	return sum_1;
}

CompExpr& CompExpr::mult_mult(){
	CompExpr& comp_sub_1 = dynamic_cast<CompExpr&>(sub_1);
	CompExpr& comp_sub_2 = dynamic_cast<CompExpr&>(sub_2);

	std::string str_2 = comp_sub_1.get_sub_2().to_string() + " * " + comp_sub_2.to_string();
	CompExpr& mul_2 = * new CompExpr{str_2,comp_sub_1.get_sub_2(),comp_sub_2,operation::mul};

	std::string str_1 = comp_sub_1.get_sub_1().to_string() + " * " + mul_2.to_string();
	CompExpr& mul_1 = * new CompExpr{str_1,comp_sub_1.get_sub_1(),mul_2,operation::mul};

	return mul_1;
}

CompExpr& CompExpr::mult_mixed(){
	CompExpr& comp_sub_1 = dynamic_cast<CompExpr&>(sub_1);
	CompExpr& comp_sub_2 = dynamic_cast<CompExpr&>(sub_2);
	bool is_first_sum    = comp_sub_1.get_op() == operation::sum;

	Expr& new_sub_1_1    = is_first_sum ? comp_sub_1.get_sub_1() : comp_sub_2.get_sub_1();
	Expr& new_sub_1_2    = is_first_sum ? comp_sub_1.get_sub_2() : comp_sub_2.get_sub_2();
	CompExpr& new_mem_2  = is_first_sum ? comp_sub_2 : comp_sub_1;

	std::string str_1_1  = new_sub_1_1.to_string() + " * " + new_mem_2.to_string();
	Expr& new_sub_1      = * new CompExpr{str_1_1,new_sub_1_1,new_mem_2,operation::mul};

	std::string str_1_2  = new_sub_1_2.to_string() + " * " + new_mem_2.to_string();
	Expr& new_sub_2      = * new CompExpr{str_1_2,new_sub_1_2,new_mem_2,operation::mul};

	std::string str = str_1_1 + " + " + str_1_2;
	return * new CompExpr{str,new_sub_1,new_sub_2,operation::sum};
}

CompExpr& CompExpr::stretch(){
	Expr& new_sub_1 = sub_1.stretch();
	Expr& new_sub_2 = sub_2.stretch();
	
	std::string op_str;
	switch(op){
		case operation::sum:
			op_str = " + ";
			break;
		case operation::mul:
			op_str = " * ";
			break;
		default:
			op_str = " ? ";
			break;
	}

	std::string str = new_sub_1.to_string() + op_str + new_sub_2.to_string();
	CompExpr new_comp{str,new_sub_1,new_sub_2,op};
	return new_comp.compute_operation();
}

CompExpr& CompExpr::extend(){
	if(is_extended())
		return *this;
	return stretch().extend();
}

bool CompExpr::is_extended(){
	bool is_comp_expr_1 = is_CompExpr(sub_1);
	bool is_comp_expr_2 = is_CompExpr(sub_2);

	if(!is_comp_expr_1 && !is_comp_expr_2)
		return true;
	if(is_comp_expr_1 != is_comp_expr_2){
		CompExpr& comp_sub = is_comp_expr_1 ? dynamic_cast<CompExpr&>(sub_1) : dynamic_cast<CompExpr&>(sub_2);
		switch(op){
			case operation::sum:
				return comp_sub.is_extended();
			case operation::mul:
				return comp_sub.is_only_mult();
			default:
				return false;
		}
	}

	CompExpr& comp_sub_1 = dynamic_cast<CompExpr&>(sub_1);
	CompExpr& comp_sub_2 = dynamic_cast<CompExpr&>(sub_2);
	switch(op){
		case operation::sum:
			return (comp_sub_1.is_only_mult() && comp_sub_2.is_extended()) || (comp_sub_1.is_extended() && comp_sub_2.is_only_mult());
		case operation::mul:
			return comp_sub_1.is_only_mult() && comp_sub_2.is_only_mult();
		default:
			return false;
	}
	
}

bool CompExpr::is_only_mult(){
	if(op == operation::sum)
		return false;
	bool is_sub_1_only_mult = true;
	bool is_sub_2_only_mult = true;
	if(is_CompExpr(sub_1))
		is_sub_1_only_mult = dynamic_cast<CompExpr&>(sub_1).is_only_mult();
	if(is_CompExpr(sub_2))
		is_sub_2_only_mult = dynamic_cast<CompExpr&>(sub_2).is_only_mult();
	
	return is_sub_1_only_mult && is_sub_2_only_mult;
}

int CompExpr::evaluate(){
	return 0;
}

// operators ---------------------------------------------------------------------------
/*
CompExpr& operator+ (const Var& v, int c){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new CompExpr{*v_e,*c_e,operation::sum};
}

CompExpr& operator+ (int c, const Var& v){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new CompExpr{*c_e,*v_e,operation::sum};
}
CompExpr& operator- (const Var& v, int c){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new CompExpr{*v_e,*c_e,operation::sub};
}
CompExpr& operator- (int c, const Var& v){
	VarExpr* v_e   = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new CompExpr{*c_e,*v_e,operation::sub};
}
CompExpr& operator* (const Var& v, int c){
	VarExpr* v_e   = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new CompExpr{*v_e,*c_e,operation::mul};
}
CompExpr& operator* (int c, const Var& v){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new CompExpr{*c_e,*v_e,operation::mul};
}
CompExpr& operator+ (const Var& v1, const Var& v2){
	VarExpr* v_e_1 = new VarExpr{v1};
	VarExpr* v_e_2 = new VarExpr{v2};
	return * new CompExpr{*v_e_1,*v_e_2,operation::sum};
}
CompExpr& operator- (const Var& v1, const Var& v2){
	VarExpr* v_e_1 = new VarExpr{v1};
	VarExpr* v_e_2 = new VarExpr{v2};
	return * new CompExpr{*v_e_1,*v_e_2,operation::sub};
}
CompExpr& operator* (const Var& v1, const Var& v2){
	VarExpr* v_e_1 = new VarExpr{v1};
	VarExpr* v_e_2 = new VarExpr{v2};
	return * new CompExpr{*v_e_1,*v_e_2,operation::mul};
}
*/
CompExpr& operator+ (CompExpr& e1, int i){
	ConstExpr* c_e = new ConstExpr{i};
	//CompExpr* e    = new CompExpr{e1};
	return * new CompExpr{e1,*c_e,operation::sum};
}

CompExpr& operator+(int i, CompExpr& e1){
	ConstExpr* c_e = new ConstExpr{i};
	//CompExpr* e    = new CompExpr{e1};
	return * new CompExpr{*c_e,e1,operation::sum};
}

CompExpr& operator- (CompExpr& e1, int i){
	ConstExpr* c_e = new ConstExpr{i};
	//CompExpr* e    = new CompExpr{e1};
	return * new CompExpr{e1,*c_e,operation::sub};
}

CompExpr& operator-(int i, CompExpr& e1){
	ConstExpr* c_e = new ConstExpr{i};
	//CompExpr* e    = new CompExpr{e1};
	return * new CompExpr{*c_e,e1,operation::sub};
}

CompExpr& operator* (CompExpr& e1, int i){
	ConstExpr* c_e = new ConstExpr{i};
	return * new CompExpr{e1,*c_e,operation::mul};
}

CompExpr& operator*(int i, CompExpr& e1){
	ConstExpr* c_e = new ConstExpr{i};
	return * new CompExpr{*c_e,e1,operation::mul};
}

CompExpr& operator+ (CompExpr& e1, const Var& v){
	VarExpr* v_e = new VarExpr{v};
	return * new CompExpr{e1,*v_e,operation::sum};
}

CompExpr& operator+(const Var& v, CompExpr& e1){
	VarExpr* v_e = new VarExpr{v};
	//CompExpr* e  = new CompExpr{e1};
	return * new CompExpr{*v_e,e1,operation::sum};
}

CompExpr& operator- (CompExpr& e1, const Var& v){
	VarExpr* v_e = new VarExpr{v};
	//CompExpr* e  = new CompExpr{e1};
	return * new CompExpr{e1,*v_e,operation::sub};
}

CompExpr& operator-(const Var& v, CompExpr& e1){
	VarExpr* v_e = new VarExpr{v};
	//CompExpr* e  = new CompExpr{e1};
	return * new CompExpr{*v_e,e1,operation::sub};
}

CompExpr& operator* (CompExpr& e1, const Var& v){
	VarExpr* v_e = new VarExpr{v};
	//CompExpr* e  = new CompExpr{e1};
	return * new CompExpr{e1,*v_e,operation::mul};
}

CompExpr& operator*(const Var& v, CompExpr& e1){
	VarExpr* v_e = new VarExpr{v};
	//CompExpr* e  = new CompExpr{e1};
	return * new CompExpr{*v_e,e1,operation::mul};
}

CompExpr& operator+(const CompExpr& e1, const CompExpr& e2){
	CompExpr& e_1 = * new CompExpr{e1};
	CompExpr& e_2 = * new CompExpr{e2};
	delete &e1;
	delete &e2;
	return * new CompExpr{e_1,e_2,operation::sum};
}

CompExpr& operator-(const CompExpr& e1, const CompExpr& e2){
	CompExpr& e_1 = * new CompExpr{e1};
	CompExpr& e_2 = * new CompExpr{e2};
	delete &e1;
	delete &e2;
	return * new CompExpr{e_1,e_2,operation::sub};
}

CompExpr& operator*(const CompExpr& e1, const CompExpr& e2){
	CompExpr& e_1 = * new CompExpr{e1};
	CompExpr& e_2 = * new CompExpr{e2};
	delete &e1;
	delete &e2;
	return * new CompExpr{e_1,e_2,operation::mul};
}
