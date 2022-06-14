#include "expr_child.h"
#include <string>

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

VarExpr& VarExpr::distr_law(){
	return *this;
}

VarExpr& VarExpr::mult(){
	return *this;
}

ConstExpr::ConstExpr(const int i):
	value{i},Expr(std::to_string(i)){}

int ConstExpr::evaluate(){
	return value;
}

ConstExpr& ConstExpr::stretch(){
	return *this;
}

ConstExpr& ConstExpr::distr_law(){
	return *this;
} 

ConstExpr& ConstExpr::mult(){
	return *this;
}

std::string CompExpr::create_string(Expr& e1, Expr& e2, const operation op){
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

bool CompExpr::is_CompExpr(Expr& ex){ return dynamic_cast<CompExpr*>(&ex); }

CompExpr::CompExpr(Expr& e1, Expr& e2, const operation op):
	sub_1{e1}, sub_2{e2}, op{op}, Expr(create_string(e1,e2,op))
	{}

CompExpr::CompExpr(const std::string& expr, const std::vector<Var>& vars, Expr& e1, Expr& e2, operation op):
	sub_1{e1},sub_2{e2},op{op},Expr(expr,vars)
	{}

operation CompExpr::get_op(){ return op; }

Expr& CompExpr::get_sub_1(){ return sub_1; }
Expr& CompExpr::get_sub_2(){ return sub_2; }

CompExpr& CompExpr::distr_law(){
	if(op != operation::mul){
		return * new CompExpr{sub_1,sub_2,op};
	}

	bool is_comp_expr_1 = is_CompExpr(sub_1);
	bool is_comp_expr_2 = is_CompExpr(sub_2);
	if(is_comp_expr_1 && is_comp_expr_2)
		return * new CompExpr{sub_1.distr_law(),sub_2.distr_law(),op};

	CompExpr& comp_sub = is_comp_expr_1 ? dynamic_cast<CompExpr&>(sub_1) : dynamic_cast<CompExpr&>(sub_2);
	Expr& sub = is_comp_expr_1 ? sub_2 : sub_1;
	Expr& mem1 = * new CompExpr{sub,comp_sub.get_sub_1(),operation::mul};
	Expr& mem2 = * new CompExpr{sub,comp_sub.get_sub_2(),operation::mul};
	return * new CompExpr{mem1,mem2,comp_sub.get_op()};
}

CompExpr& CompExpr::mult(){
	bool is_comp_expr_1 = is_CompExpr(sub_1);
	bool is_comp_expr_2 = is_CompExpr(sub_2);
	
	if(!is_comp_expr_1 && !is_comp_expr_2)
		return * new CompExpr{sub_1,sub_2,op};

	if(is_comp_expr_1 != is_comp_expr_2){
		CompExpr& sub_comp = is_comp_expr_1 ? dynamic_cast<CompExpr&>(sub_1) : dynamic_cast<CompExpr&>(sub_2);
		operation sub_op = sub_comp.get_op();
		switch(sub_op){
			case operation::sum:
				return this->distr_law();
			case operation::mul:{
				std::string mem2 = sub_comp.to_string();
				std::string mul = sub_1.to_string() + " * " + sub_2.to_string();
				return * new CompExpr{mul,this->vars,sub_1,sub_2,op};
			    }
		}
	}
	
	CompExpr& comp_sub_1 = dynamic_cast<CompExpr&>(sub_1);
	operation op_sub_1 = comp_sub_1.get_op();
	CompExpr& comp_sub_2 = dynamic_cast<CompExpr&>(sub_2);
	operation op_sub_2 = comp_sub_2.get_op();
	
	if(op_sub_1 == operation::sum && op_sub_2 == operation::sum){
		CompExpr& new_sub_1_1 = * new CompExpr{comp_sub_1.get_sub_1(),comp_sub_2.get_sub_1(),operation::mul};
		CompExpr& new_sub_1_2 = * new CompExpr{comp_sub_1.get_sub_1(),comp_sub_2.get_sub_2(),operation::mul};
		CompExpr& new_sub_1   = * new CompExpr{new_sub_1_1,new_sub_1_2,operation::sum};
		
		CompExpr& new_sub_2_1 = * new CompExpr{comp_sub_1.get_sub_2(),comp_sub_2.get_sub_1(),operation::mul};
		CompExpr& new_sub_2_2 = * new CompExpr{comp_sub_1.get_sub_2(),comp_sub_2.get_sub_2(),operation::mul};
		CompExpr& new_sub_2   = * new CompExpr(new_sub_2_1,new_sub_2_2,operation::sum);
		
		return * new CompExpr{new_sub_1,new_sub_2,operation::sum};
	}
	
	if(op_sub_1 == operation::mul && op_sub_2 == operation::mul){
		std::string mem1 = sub_1.to_string();
		std::string mem2 = sub_2.to_string();
		std::string mul  = mem1 + " * " + mem2;
		return * new CompExpr{mul,this->vars,sub_1,sub_2,operation::mul};
	}

	bool is_first_sum = comp_sub_1.get_op() == operation::sum;
	Expr& new_sub_1_1 = is_first_sum ? comp_sub_1.get_sub_1() : comp_sub_2.get_sub_1();
	Expr& new_sub_1_2 = is_first_sum ? comp_sub_1.get_sub_2() : comp_sub_2.get_sub_2();
	CompExpr& new_mem_2    = is_first_sum ? comp_sub_2 : comp_sub_1;
	Expr& new_sub_1 = * new CompExpr{new_sub_1_1,new_mem_2,operation::mul};
	Expr& new_sub_2 = * new CompExpr{new_sub_1_2,new_mem_2,operation::mul};
	return * new CompExpr{new_sub_1,new_sub_2,operation::sum};
}

CompExpr& CompExpr::stretch(){
	CompExpr& comp_sub_1 = dynamic_cast<CompExpr&>(sub_1);
	CompExpr& comp_sub_2 = dynamic_cast<CompExpr&>(sub_2);
		switch(op){
			case operation::sum:{
					std::string mem1 = sub_1.stretch().to_string();
					std::string mem2 = sub_2.stretch().to_string();
					std::string sum = mem1 + " + " + mem2;
					return * new CompExpr{sum,this->vars,sub_1,sub_2,op};
					break;
					}

			case operation::sub:{/*
					std::string mem1 = sub_1.stretch().tostring();
					std::string mem2;
					if(dynamic_cast<CompExpr*>(&sub2))
						mem2 = 
					else{
						mem2 = sub_2.to_string();
					}
					break;*/
					}
			case operation::mul:{
					CompExpr& str = this->mult();
					return * new CompExpr{str.get_sub_1().stretch(),str.get_sub_2().stretch(),str.get_op()};
					}
			default:
				return *this;
				break;
		}
	return *this;
}

int CompExpr::evaluate(){
	return 0;
}

// operators ---------------------------------------------------------------------------

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
