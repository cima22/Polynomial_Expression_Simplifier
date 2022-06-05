#include <iostream>

class Var{
	private:
		std::string name;
		float value;
	
	public:
		Var(const std::string& name, const float value);
		std::string& get_name();
		friend std::ostream& operator<<(std::ostream& os, const Var& v);
};
