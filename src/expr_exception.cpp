#include "expr_exception.h"

NotMonomial::NotMonomial():
	message{"The expression is not a monomial"}{}

NotMonomial::NotMonomial(std::string message):
	message{message}{}
