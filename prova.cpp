#include <iostream>
#include <vector>
#include <map>
#include <memory>

class Try{
	private:
	int i;
	std::string s;
	public:
	Try(){
		std::cout << "Default constructor" << std::endl;
	}
	Try(int i):i{i}{
		std::cout << "Custom constructor" << std::endl;
	}
	Try(int i,std::string s):i{i},s{s}{}
	const int get_i() const {return i;}
	virtual void printa() = 0;
};

class Try_child : public Try{
	public:
	Try_child(int i) : Try(i){std::cout<<"Custom try_child";}

	Try_child(int i, std::string s): Try(i,s){}

	void printa() override {
		std::cout << "\nTry_child" << std::endl;
	}

};

class Try_child_2 : public Try{
	public:
	Try_child_2(int i) : Try(i){std::cout<<"Custom try_child_2";}

	void printa() override{
		std::cout << "\nTry_child_2" << std::endl;
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

enum type {one,two};

struct Try_container{
	//std::shared_ptr<Try> obj;
	Try * obj;
	Try_container(int i,type t){
		switch(t){
			case one:
				//obj = std::shared_ptr<Try>(new Try_child{i});
				obj = new Try_child{i};
				break;
			case two:
				//obj = std::shared_ptr<Try>(new Try_child_2{i});
				obj = new Try_child_2{i};
				break;
		}
	}

	void printa(){
		obj->printa();
	}
};

void test(Try_child& bu){
	std::cout << "ciao";
}

int main(){
	/*
	Try_child tc{3};
	Try_child tc1{34};
	Try_child tc2{1};
	Try_child_2 tc3{4};
	Try_child_2 tc4{5};
	Try& tc5 = tc1 + tc2 + tc1;
	Try& tc6 = tc3 + tc4;
	std::cout << "\n" << tc1.get_i() << "\n" << tc2.get_i() << "\n " << tc5.get_i() << std::endl;
	*/
	Try_child tc{3,"ciao"};

	Try_container t{3,one};
	Try_container t2{1,two};

	t.printa();
	t2.printa();
	
}
