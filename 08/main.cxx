#include <iostream>

#include "functions.h"

struct A 
{ 
	int x;
};

void foo(const A& a) 
{
	std::cout << a.x << std::endl; 
}

int main ()
{
	ThreadPool pool(4);

	auto task1 = pool.exec(foo, A{10});
	task1.get();

	auto task2 = pool.exec([]() { return 10; });
	std::cout << task2.get() << std::endl;
	
	for (int i = 0; i <= 10; ++i)
	{
		std::cout << pool.exec([i](){ return i;}).get() << " ";
	}
	std::cout << "\n";
}
