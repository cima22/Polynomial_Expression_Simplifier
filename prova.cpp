#include <iostream>
#include <vector>
#include <map>

class Try{
	private:
	int i;
	public:
	Try(){
		std::cout << "Default constructor" << std::endl;
	}
	Try(int i):i{i}{
		std::cout << "Custom constructor" << std::endl;
	}/*
	virtual void printa(){
		std::cout << "Try" << std::endl;}*/
	const int get_i() const {return i;}
	virtual void printa() = 0;
};

class Try_child : public Try{
	public:
	Try_child(int i) : Try(i){std::cout<<"Custom try_child";}

	void printa() override {
		std::cout << "Try_child" << std::endl;
	}
};

class Try_child_2 : public Try{
	public:
	Try_child_2(int i) : Try(i){std::cout<<"Custom try_child_2";}

	void printa() override{
		std::cout << "Try_child_2" << std::endl;
	}
};

Try_child& operator+(const Try_child& op1, const Try_child& op2){
	int res = op1.get_i() + op2.get_i();
	return * new Try_child{res};
}

Try_child_2& operator+(const Try_child_2& op1, const Try_child_2& op2){
	int res = op1.get_i() + op2.get_i();
	return * new Try_child_2{res};
}

int main(){
	
	// Try_child tc{3};
	Try_child tc1{34};
	Try_child tc2{1};
	Try_child_2 tc3{4};
	Try_child_2 tc4{5};
	Try& tc5 = tc1 + tc2;
	Try& tc6 = tc3 + tc4;
	tc5.printa();
	tc6.printa();
	
}
