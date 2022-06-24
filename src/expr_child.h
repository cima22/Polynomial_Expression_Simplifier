#include "expr_parent.h"
#include <string>
#include <map>
#include <memory>
#include <queue>

class VarExpr : public ParentExpr{ // Expression which is composed only by one variable, e.g.: x
	private:
		bool is_extended() const override; // checks if the expression is in the form of sum of monomials (it is always true for VarExpr)

	public:
		// Constructors & Destructor
		VarExpr(const Var& v);
		virtual ~VarExpr();
		
		// Public methods

		void set_value(int v); // to set the value of the variable
		bool is_only_mult()      const override;
		const VarExpr& clone()   const override;
		static bool is_VarExpr(const ParentExpr& ex); // static method to check if the reference is to an instance of VarExpr
		
		// Methods that can be used only if the expression is a monomial (in this case it is always a monomial)
		int get_degree(const Var& v) const override;
		int get_monomial_const() const override;

		// Override of methods of parent class to make the expressions as a sum of monomials (in this case it is sufficient to return the expression)

		const VarExpr&    stretch() const override;
		const VarExpr&    extend()  const override;
		const ParentExpr& unroll()  const override;

		const ParentExpr& replace(const std::map<Var,const ParentExpr*>& repl) const override;

		std::map<unsigned int,const ParentExpr*> get_coeffs(const Var& v) const override;
		const ParentExpr& extract_monomial(const Var& v) const override;
		void insert_coeff(std::map<unsigned int, const ParentExpr*>& coeffs,const Var& v) const override;
		
		std::pair<int,std::map<Var,unsigned int>> get_monomial() const override;
		std::vector<std::pair<int,std::map<Var,unsigned int>>> get_vector_of_monomials() const override;
};

class ConstExpr : public ParentExpr{ // Expression which is composed only by one constant, e.g.: 2
	private:
		int value;
		bool is_extended() const override; // checks if the expression is in the form of sum of monomials (it is always true for ConstExpr)

	public:
		// Constructor & Destructor
		ConstExpr(const int i);
		virtual ~ConstExpr();
		
		// Public methods

		const ConstExpr& clone() const override;
		bool is_only_mult()      const override;
		static bool is_ConstExpr(const ParentExpr& ex); // static method to check if the reference is to an instance of ConstExpr
		
		// Methods that can be used only if the expression is a monomial (in this case it is always a monomial)
		int get_degree(const Var& v) const override;
		int get_monomial_const() const override;

		// Override of methods of parent class to make the expressions as a sum of monomials (in this case is sufficient to return the expression)

		const ConstExpr& stretch() const override;
		const ConstExpr& extend()  const override;
		const ParentExpr& unroll() const override;
		
		const ParentExpr& replace(const std::map<Var,const ParentExpr*>& repl) const override;

		std::map<unsigned int,const ParentExpr*> get_coeffs(const Var& v) const override;
		const ConstExpr& extract_monomial(const Var& v) const override;
		void insert_coeff(std::map<unsigned int, const ParentExpr*>& coeffs,const Var& v) const override;
		
		std::pair<int,std::map<Var,unsigned int>> get_monomial() const override;
		std::vector<std::pair<int,std::map<Var,unsigned int>>> get_vector_of_monomials() const override;
};

enum class operation {sum, sub, mul};

class CompExpr : public ParentExpr{ // Exression which is a Compound-Expression, that is it is composed by the sum, subtraction or multiplication of two expressions
	private:
		// A compound expression is composed of two references to two sub-expressions and an operation between the two
		const ParentExpr& sub_1;
		const ParentExpr& sub_2;
		operation op;

		std::string create_string(const ParentExpr& e1, const ParentExpr& e2, operation op); // creates the string format in the constructor given the two sub-expressions and the operation
		bool is_extended() const override; // checks if the expression is in the form of sum of monomials
			
		// Private methods which defines how the compound expressions should behave with the operation between the two sub-expressions. For example, is the compound expression is composed of 
		// a Const or Var Expr and a multiplication with a compound expression which internally sums two expressions, the distributive law is used to return an equivalent expression where the sum
		// is distributed accordingly. The method "compute_operation" performs the operation that is intended by the compound expression, and based on the characteristics of the expression 
		// (operation and type of sub-expressions) the other methods are called.

		const CompExpr& compute_operation();
	
		// More specific operations, called by compute_operation
		const CompExpr& sum_simple_comp();  // sum of a simple expression (constant or variable) and a compound expression
		const CompExpr& mult_simple_comp(); // multiplication of a simple expr and a compound expr
		const CompExpr& distr_law();        // distributive law, e.g. multiplication of simple expr and compound expr with sum 
		
		const CompExpr& compound_sum();     // sum between two comp expr, which specifies into three methods:
		const CompExpr& sum_sum();          // sum of two sum-compound expr
		const CompExpr& sum_mult();         // sum of two mult-comp expr
		const CompExpr& sum_mixed();        //sum of one sum-comp expr and one mult-comp expr

		const CompExpr& compound_mult();    //multiplication between two comp expr, which specifies into three methods:
		const CompExpr& mult_sum();         // multiplication of two sum-comp expr
		const CompExpr& mult_mult();        // multiplication of two mult-comp expr
		const CompExpr& mult_mixed();       // multiplication of one sum-comp expr and one mult-comp expr


	public:
		// Constructors & Destructors

		CompExpr(const ParentExpr& e1, const ParentExpr& e2, operation op);
		CompExpr(const std::string& expr, const ParentExpr& e1, const ParentExpr& e2, operation op);
		CompExpr(const std::string& expr, const std::vector<Var>& vars, const ParentExpr& e1, const ParentExpr& e2, operation op);
		CompExpr(const CompExpr& comp);
		virtual ~CompExpr();	
		
		// Public methods
		
		const operation get_op()      const;
		const ParentExpr& get_sub_1() const;
		const ParentExpr& get_sub_2() const;
		bool  is_only_mult()          const override;
		const CompExpr& clone()       const override;
		static bool is_CompExpr(const ParentExpr& ex); // checks if the reference is to an instance of CompExpr
		static const ParentExpr& create_monomial(const Var& v, unsigned int degree); // static method which given a variable and a degree, returns the monomial x**degree 
									// e.g. create_monomial(x,4) creates the expression x*x*x*x
		static const ParentExpr& create_monomial(std::pair<int,std::map<Var,unsigned int>> monomial); // static method which takes in input an std::pair; the first element is the
									// constant part of the monmial, while the second element is a map which maps every variable with its degree
									// e.g. create_monomial(< 4 , < x::2, y::2, z::1 > >) = 4 * x * x * y * y * z
		
		// Methods that can be used only if the expression is a monomial
		int get_monomial_const() const override;
		int get_degree(const Var& v) const override;
		std::pair<int,std::map<Var,unsigned int>> get_monomial() const override; // Returns the monomial in the form of std::pair;
		const ParentExpr& ordered_monomial() const; // Returns an expression which is the same monomial, but ordered: the variables are in alphabetic order and all the constant part are
							    // multiplied into one

		// Override of methods of parent class to make the expressions as a sum of monomials (in this case is sufficient to return the expression)
		const CompExpr&   stretch() const override; // Recursively performs stretch to its sub-expressions in order to distribute the sums and multiplications. 
							    // Since it is not enough to obtain a form of sum of monomials, the extend() methods comes to help.
		const CompExpr&   extend()  const override; // Performs stretch() until the expression is in the form of sum of monomials
		const ParentExpr& unroll()  const override; // Performs extend() and then sums all the monomials with the same degree. This method is also available to the "interface" Expr.
		
		const ParentExpr& replace(const std::map<Var,const ParentExpr*>& repl) const override;

		std::map<unsigned int,const ParentExpr*> get_coeffs(const Var& x) const override;
		void insert_coeff(std::map<unsigned int,const ParentExpr*>& coeffs,const Var& v) const override;
		const ParentExpr& extract_monomial(const Var& v) const override;

		std::vector<std::pair<int,std::map<Var,unsigned int>>> get_vector_of_monomials() const override;

		// Friend operators

		friend const CompExpr& operator+ (const CompExpr& e1, const CompExpr& e2);
		friend const CompExpr& operator- (const CompExpr& e1, const CompExpr& e2);
		friend const CompExpr& operator* (const CompExpr& e1, const CompExpr& e2);

		friend const CompExpr& operator+ (const CompExpr& e1, int i);
		friend const CompExpr& operator+ (int i, const CompExpr& e1);

		friend const CompExpr& operator- (const CompExpr& e1, int i);
		friend const CompExpr& operator- (int i, const CompExpr& e1);
		
		friend const CompExpr& operator* (const CompExpr& e1, int i);
		friend const CompExpr& operator* (int i, const CompExpr& e1);

		friend const CompExpr& operator+ (const CompExpr& e1, const Var& v1);
		friend const CompExpr& operator+ (const Var& v1, const CompExpr& e1);

		friend const CompExpr& operator- (const CompExpr& e1, const Var& v1);
		friend const CompExpr& operator- (const Var& v1, const CompExpr& e1);

		friend const CompExpr& operator* (const CompExpr& e1, const Var& v1);
		friend const CompExpr& operator* (const Var& v1, const CompExpr& e1);
};

const CompExpr& operator+ (const Var& v, int c);
const CompExpr& operator+ (int c, const Var& v);
const CompExpr& operator- (const Var& v, int c);
const CompExpr& operator- (int c, const Var& v);
const CompExpr& operator* (const Var& v, int c);
const CompExpr& operator* (int c, const Var& v);
const CompExpr& operator+ (const Var& v1, const Var& v2);
const CompExpr& operator- (const Var& v1, const Var& v2);
const CompExpr& operator* (const Var& v1, const Var& v2);
