// ref.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <cmath>
#include <functional>
#include "pch.h"
//using namespace std;

#include <boost/ref.hpp>
using namespace boost;

struct square
{
	typedef void result_type;
	result_type operator()(int &x)
	{
		std::cout << " square of "<<x ;
		x = x * x;
		std::cout <<" is " << x << std::endl;

	}
};

//////////////////////////////////////////

void case1()
{
	std::cout << " start case1()" << std::endl;

	std::vector<int> v = { 1,2,3,4,5 };
	for_each(v.begin(), v.end(), square());

	std::cout << " start case1()" << std::endl;

}

//////////////////////////////////////////

void case2()
{

	std::cout << " start case2()" << std::endl;

	int x = 10;
	reference_wrapper<int> rw(x);
	assert(x == rw);
	(int &)rw = 100;
	assert(x == 100);

	reference_wrapper<int> rw2(rw);
	assert(rw2.get() == 100);

	std::string str;
	reference_wrapper<std::string> rws(str);
	*rws.get_pointer() = "test reference_wrapper";
	std::cout << rws.get() << std::endl;
	std::cout << rws.get().size() << std::endl;

	std::cout << " end case2()" << std::endl;

}

//////////////////////////////////////////

void case3()
{
	double x = 2.71828;
	auto rw = cref(x);
	std::cout << typeid(rw).name() << std::endl;

	std::string str;
	auto rws = boost::ref(str);
	std::cout << typeid(rws).name() << std::endl;

	boost::cref(str);   //adl

	std::cout << std::sqrt(ref(x)) << std::endl;      //璁＄畻骞虫柟鏍?
}

//////////////////////////////////////////

void case4()
{
	std::cout << " start case4()" << std::endl;

	std::vector<int> v(10, 2);
	auto rw = boost::cref(v);

	assert(is_reference_wrapper<decltype(rw)>::value);
	assert(!is_reference_wrapper<decltype(v)>::value);

	std::string str;
	auto rws = boost::ref(str);
	std::cout << typeid(unwrap_reference<decltype(rws)>::type).name() << std::endl;
	std::cout << typeid(unwrap_reference<decltype(str)>::type).name() << std::endl;
	std::cout << " end case4()" << std::endl;

}

//////////////////////////////////////////

void case5()
{

	std::cout << "start case5()" << std::endl;

	std::set<int> s;
	auto rw = boost::ref(s);
	unwrap_ref(rw).insert(12);

	std::string str("test");
	auto rws = boost::cref(str);

	std::cout << unwrap_ref(rws) << std::endl;
	std::cout << rws.get() << std::endl;
	std::cout << unwrap_ref(str) << std::endl;
	std::cout << "end case5()" << std::endl;

}

//////////////////////////////////////////

class big_class
{
private:
	int x;
public:
	big_class() :x(0) {}
	void print()
	{
		std::cout << "big_class " << ++x << std::endl;
	}
};
template<typename T>
void print(T a)
{
	for (int i = 0; i < 2; ++i)
		unwrap_ref(a).print();
}
void case6()
{
	std::cout << " start case6()" << std::endl;

	big_class c;
	auto rw = ref(c);
	c.print();

	print(c);
	
	print(rw);
	
	print(c);
	
	c.print();
	
	std::cout << " end case6()" << std::endl;

}

void case7()
{

	std::cout << " start case7()" << std::endl;

	using namespace std;

	typedef double(*pfunc)(double);
	pfunc pf = sqrt;  //包装函数指针
	cout << std::ref(pf)(5.0) << endl;

	square sq;
	int x = 5;
	std::ref(sq)(x); //包装函数对象
	cout << x << endl;

	vector<int> v = { 1,22,3,14,5 };

	sort(v.begin(), v.end());

	for_each(v.begin(), v.end(), std::ref(sq)); //传递给算法引用

	std::cout << " end case7()" << std::endl;


}


int main()
{
	case1();
	case2();
	case3();
	case4();
	case5();
	case6();
	case7();
}
