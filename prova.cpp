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
};

int main(){
	
	std::map<std::string, int> m {{"ciao",1},{"come",2},{"va",3}};
	std::cout << m["va"] << std::endl;
	
	Try t1;
	Try t2{3};
	Try t3{};
	

}
