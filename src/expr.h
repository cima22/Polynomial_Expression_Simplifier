#ifndef _EXPR_
#define _EXPR_

#include <vector>
#include <algorithm>
#include "var.h"

class Expr{
	
	private:
		std::string expression; // string format of the expression
		std::vector<Var> vars;  // vector of variables
		
		void extract_vars();

	public:
		Expr(const std::string& expr);
		Expr(const std::string& expr, const std::vector<Var>& vars);

		friend std::ostream& operator<<(std::ostream& os, const Expr& expr);
		//template <typename T>
		friend Expr operator+(const Var& v, int i);
		friend Expr operator+(const Expr& e1, const Expr& e2);
		friend Expr operator+(const Expr& e1, int i);	
};
#endif
