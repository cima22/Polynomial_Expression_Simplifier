#include <vector>
#include <string>
#include "var.h"

class Expr{
	private:

	std::string expression; // string format of the expression
	std::vector<Var> vars;  // vector of variables

	public:

	Expr(const std::string& expression);

	friend std::ostream& operator<< (std::ostream& os, const Expr& expr);
};
