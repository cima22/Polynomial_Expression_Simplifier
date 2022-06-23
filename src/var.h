#ifndef _VAR_
#define _VAR_

#include <iostream>
#include <string>

/*
 * Class which represents variables. Every variable has a name and a possible value;
 */

class Var{
	private:
		std::string name; // name of the variable
		float value;      // value of the variable 
	
	public:
		// Constructors

		Var(const std::string& name, const float value);
		Var(const std::string& name);
		
		// Public Methods

		const std::string& get_name() const;
		void               set_name(const std::string& new_name);
		const float        get_value() const;
		void               set_value(const float new_value);
		
		// Friend operators

		friend std::ostream& operator<< (std::ostream& os, const Var& v);
		friend bool operator< (const Var& v1, const Var& v2);
		friend bool operator== (const Var& v1, const Var& v2);
};

#endif
