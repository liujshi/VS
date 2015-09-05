// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Algorithm.h"
#include "SmartPointer.h"
#include "allocator.h"
#include <iostream>
#include "vector.h"
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
	int i3[] = { 0, 0, 0, 0, 0 };
	LSTL::vector<int, LSTL::allocator<int> >iv(ia, ia + 5);
	LSTL::vector<int> ii(i3, i3 + 5);
	for (auto e:ii)
	{
		cout << e << "\t";
	}

	cout << endl;

	LSTL::copy_backward(iv.begin(), iv.end(), ii.end());
	for (auto e : ii)
	{
		cout << e << "\t";
	}
	cout << endl;
	cout << LSTL::Profiler::ProfilerInstance::memory() << endl;
	return 0;

}

