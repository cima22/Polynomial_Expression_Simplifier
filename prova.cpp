#include <iostream>
#include <vector>

struct Try{
	int i;
	Try(int i):i{i}{};
};

struct Fu{
	std::vector<Try> vars;
	Fu(std::vector<Try> arg):vars{arg}{};
	std::vector<Try> func(){return vars;} 
};

int main(){
	
	Try e1{1};
	/*
	Try e2{2};
	
	std::vector<Try> v1{e1,e2};

	Fu f1{v1};

	Try e3{3};
	v1.push_back(e3);

	for(auto& e : v1)
		std::cout << e.i << "\n";

	for(auto& e : f1.func())
		std::cout << e.i << "\n";
	*/
	std::vector<Try> v1{e1};
	e1.i = 2;
	std::cout << v1[0].i << std::endl;
	if(1)
		std::cout << "aaaaaa";
}
