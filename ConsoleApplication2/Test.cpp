// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "SmartPointer.h"
#include <iostream>
#include <string>
using namespace std;
using namespace LIUSTL;

class A{
public:
	A(){
		cout << "A_Constructed!" << endl;
	}
	~A(){
		cout << "A_Destructed!" << endl;
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Hello_My_Git!" << endl;
	A *a = new A;
	SPtr<A>sp=new SPtr<A>;
	sp = a;
	auto sp1(a);

	return 0;

}

