#include "var.h"

Var::Var(const std::string& name, const float value):
	name{name},value{value}
	{}

Var::Var(const std::string& name):
	name{name}
	{}

std::string& Var::get_name(){ return name; }

float Var::get_value(){ return value; }
void Var::set_value(const float new_value){ value = new_value; }

std::ostream& operator<<(std::ostream& os, const Var& v){
	os << v.name << " = " << v.value;
	return os;
}
