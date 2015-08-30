// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "SmartPointer.h"
#include "allocator.h"
#include <iostream>
#include <string>
#include <vector>
#include "Testtools.h"
using namespace std;

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
	/*cout << "Hello_My_Git!" << endl;
	A *a = new A;
	SPtr<A>sp=new SPtr<A>;
	sp = a;
	auto sp1(a);*/

	int ia[] = { 1, 2, 3, 4, 5 };

	vector<int, LSTL::allocator<int> >iv(ia, ia + 5);
	for (auto e:iv)
	{
		cout << e << "\t";
	}
	cout << endl;
	cout << LSTL::Profiler::ProfilerInstance::memory() << endl;
	return 0;

}

