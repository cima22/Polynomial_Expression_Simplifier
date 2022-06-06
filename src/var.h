#include <iostream>

class Var{
	private:
		std::string name; // name of the variable
		float value;      // value of the variable 
	
	public:
		Var(const std::string& name, const float value);
		Var(const std::string& name);
		
		std::string& get_name();
		float get_value();
		void set_value(const float value);
		
		friend std::ostream& operator<<(std::ostream& os, const Var& v);
};
