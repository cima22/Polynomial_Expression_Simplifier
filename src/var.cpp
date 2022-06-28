#include "var.h"

Var::Var(const std::string& name, const float value):
	name{name},value{value}
	{}

Var::Var(const std::string& name):
	name{name}
	{}

const std::string& Var::get_name() const { return name; }
void               Var::set_name(const std::string& new_name){ name = new_name; };

const float        Var::get_value() const {return value;}
void               Var::set_value(const float new_value){ value = new_value; }

std::ostream& operator<< (std::ostream& os, const Var& v){
	os << v.name;
	return os;
}

bool operator< (const Var& v1, const Var& v2){
	return v1.get_name() < v2.get_name();
}

bool operator== (const Var& v1, const Var& v2){
	return v1.get_name() == v2.get_name();
}
