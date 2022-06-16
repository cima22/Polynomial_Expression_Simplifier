#include "var.h"

Var::Var(const std::string& name, const float value):
	name{name},value{value}
	{}

Var::Var(const std::string& name):
	name{name}
	{}

std::string       Var::get_name(){ return name; }
const std::string& Var::get_name() const {return name;}
void               Var::set_name(const std::string& new_name){ name = new_name; };

float              Var::get_value(){ return value; }
const float        Var::get_value() const {return value;}
void               Var::set_value(const float new_value){ value = new_value; }

std::ostream& operator<< (std::ostream& os, const Var& v){
	os << v.name << " = " << v.value;
	return os;
}

