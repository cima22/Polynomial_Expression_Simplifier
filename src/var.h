#ifndef _VAR_
#define _VAR_

#include <iostream>
#include <string>

class Var{
	private:
		std::string name; // name of the variable
		float value;      // value of the variable 
	
	public:
		Var(const std::string& name, const float value);
		Var(const std::string& name);
		
		std::string       get_name();
		const std::string& get_name() const;
		void               set_name(const std::string& new_name);
		float              get_value();
		const float        get_value() const;
		void               set_value(const float new_value);
		
		friend std::ostream& operator<< (std::ostream& os, const Var& v);
		//friend Var           operator+  (const Var& v1, const Var& v2);
		//friend Var           operator-  (const Var& v1, const Var& v2);
		//friend Var           operator*  (const Var& v1, const Var& v2);
		//friend Var operator+(const Var& v1, int i);
};

#endif
