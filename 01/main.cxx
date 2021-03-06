#include "functions.h"

int main()
{
	makeAllocator(1024);
	char* p1 = alloc(100);
	char* p2 = alloc(300);
	char* p0 = alloc(0);
	char* p3 = alloc(600);
	char* p4 = alloc(1000);
	reset();
	char* p5 = alloc(1024);
	char* p6 = alloc(1);
    
	makeAllocator(pow(10,12)); //memory error
	char* p7 = alloc(1);
    
	if (p2 - p1 != 100)
	{
		std::cout << "BAD_1" << std::endl;
		return 1;
	}
	
	if (p3 != p0)
	{
		std::cout << "BAD_2" << std::endl;
	return 1;
	}

	if (p4 != nullptr)
	{
		std::cout << "BAD_3" << std::endl;
		return 1;
	}

	if (p5 == nullptr)
	{
		std::cout << "BAD_4" << std::endl;
		return 1;
	}

	if (p6 != nullptr)
	{
		std::cout << "BAD_5" << std::endl;
		return 1;
	}
	
	if (p7 != nullptr)
	{
		std::cout << "BAD_6" << std::endl;
		return 1;
	}

	std::cout << "ALL TESTS ARE SUCCESSFUL" << std::endl;

	return 0;
}
