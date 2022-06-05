#include "var.h"

Var::Var(const std::string& name, const float value):
	name{name},value{value}
	{}

std::string& Var::get_name(){ return name; }

std::ostream& operator<<(std::ostream& os, const Var& v){
	os << v.name << " = " << v.value;
	return os;
}
