#include <iostream>


template <typename T>
class A
{
public:
	A(const T& y) : x(y) {}

	template <typename Function>
	void process(const Function& fun)
	{
		fun(x);
	}

private:
	T x;
};


int main()
{
	A<int> x(10);

	x.process([](int x) { std::cout << x << std::endl; });

	return 0;
}