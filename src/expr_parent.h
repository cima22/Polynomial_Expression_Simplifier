#ifndef _EXPR_
#define _EXPR_

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "var.h"

class ParentExpr{
	
	protected:
		std::string expression; 	// string format of the expression
		std::vector<Var> vars;  	// vector of variables

		void extract_vars();

	public:
		ParentExpr();
		ParentExpr(const std::string& expr);
		ParentExpr(const std::string& expr, const std::vector<Var>& vars);
		virtual ~ParentExpr() = 0;
		std::vector<Var> get_variables() const;
		const std::string& to_string() const;

		virtual int 	evaluate() 		       = 0;
		const virtual 	ParentExpr& stretch() 	 const = 0;
		const virtual 	ParentExpr& extend() 	 const = 0;
		virtual bool 	is_extended() 		 const = 0;
		virtual bool 	is_only_mult() 		 const = 0;
		virtual int	get_degree(const Var& v) const = 0;
		virtual const ParentExpr& extract_monomial(const Var& v) const = 0;
		virtual std::map<unsigned int,const ParentExpr*> get_coeffs(const Var& v) const = 0;	
		virtual const ParentExpr& replace(const std::map<Var,const ParentExpr*>& repl) const = 0;
		virtual const ParentExpr& clone() const = 0;
		virtual void insert_coeff(std::map<unsigned int,const ParentExpr*>& coeffs, const Var& v) const = 0;

		friend std::ostream& operator<<(std::ostream& os, const ParentExpr& expr);
		friend bool equal (const ParentExpr& e1, const ParentExpr& e2);
		virtual int get_monomial_const() const = 0;
		virtual const ParentExpr& extend_and_group() const = 0;
		virtual std::vector<std::pair<int,std::map<Var,unsigned int>>> get_vector_of_monomials() const = 0;
		void insert_monomial(std::vector<std::pair<int,std::map<Var,unsigned int>>>& vec) const;
		virtual std::pair<int,std::map<Var,unsigned int>> get_monomial() const = 0;
		virtual const ParentExpr& unroll() const = 0;
};

bool are_same_type(const ParentExpr& e1, const ParentExpr& e2);
#endif
