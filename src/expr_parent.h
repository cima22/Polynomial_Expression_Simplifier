#ifndef _EXPR_
#define _EXPR_

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "var.h"

typedef std::pair<int,std::map<Var,unsigned int>> monomial;

/*
 * Class which represents the actual expression. Since every expression is either a constant, a single variable or a sum/subtraction/multiplication of other two expressions,
 * this is an abstract class representing a general expression. Three more derived classes are defined to handle every case described above.
 */

class ParentExpr{
	
	protected:
		std::string expression; 	// string format of the expression
		std::vector<Var> vars;  	// vector of variables

		void extract_vars(); 		// method which extracts the variables out of the string format of the expression

	public:
		// Constructors & virtual destructor

		ParentExpr();
		ParentExpr(const std::string& expr);
		ParentExpr(const std::string& expr, const std::vector<Var>& vars);

		ParentExpr(const ParentExpr& expr) = default;
		ParentExpr(ParentExpr&& expr)      = default;

		virtual ~ParentExpr() = 0;

		// Public methods 
	
		std::vector<Var> 	  get_variables()          const;
		const std::string& 	  to_string() 		   const;
		virtual const ParentExpr& clone() 		   const = 0; // returns a copy of the expression
		virtual bool     	  is_only_mult()           const = 0; // checks if the expression is a monomial, i.e. it is composed of only multiplications (or it is a constant or a variable)
		ParentExpr& operator=(const ParentExpr& expr) = default;
		ParentExpr& operator=(ParentExpr&& expr)      = default;

		 // Methods that works only if the expression is a monomial
		virtual int  get_degree(const Var& v) const = 0; // Return the degree of the given variable of the monomial
		virtual int  get_monomial_const()     const = 0; // Return the constant part of the monomial (e.g. if monomial is 3 * x * y * 2 the constant part is 6)
		virtual void insert_coeff(std::map<unsigned int,const ParentExpr*>& coeffs, const Var& v) const = 0; // Inserts the coeffictient in the map relative to the degre of the variable
					// in the monomial; if the degree is already present in the map, it sums the coeffictient with the already present coeffictient
		
		// Methods to get the expression in the form of a sum of monomials
		virtual bool 		  is_extended()  const = 0; // check if the expression is in form of a sum of monomials
		virtual const ParentExpr& stretch() 	 const = 0; // return an expression which is a "stretched" version of the caller 
								    //(performs multiplications in the internal expressions in  order to distibute the sums)
		virtual const ParentExpr& extend() 	 const = 0; // performs the stretching until the expression is in a form of a sum of monomials
		virtual const ParentExpr& unroll()       const = 0; // performs the extension and then sums the monomials with the same variables
		virtual const ParentExpr& extract_monomial(const Var& v) const = 0;

		virtual std::map<unsigned int,const ParentExpr*> get_coeffs(const Var& v) const = 0;	

		virtual const ParentExpr& replace(const std::map<Var,const ParentExpr*>& repl) const = 0;

		virtual std::vector<monomial> get_vector_of_monomials() const = 0; // returns the vector of monomials which composes the expressions. 
					//A monomial is in the form of a pair, where the first entry is the constant part and the second a map which maps every variable with its degree in the monomial
		void insert_monomial(std::vector<monomial>& vec) const;
		virtual monomial get_monomial() const = 0;
		
		// Friend operators
		friend std::ostream& operator<<(std::ostream& os, const ParentExpr& expr);
		friend bool equal (const ParentExpr& e1, const ParentExpr& e2);
};
#endif
