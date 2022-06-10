#include <iostream>
#include <vector>
#include <map>

struct Try{
	int i;
	Try(){
		std::cout << "Default constructor";
	}
	Try(int i):i{i}{
		std::cout << "Custom constructor";
	}
	virtual void printa() = 0;
};

struct Try_child : public Try{

	void printa() override {
		std::cout << "ciao";
	}
};

int main(){
	
	Try* t = new Try_child{};
	t->printa();
	
}
