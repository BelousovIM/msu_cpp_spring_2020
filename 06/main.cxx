#include "functions.h"

int main() 
{

	assert(format("{0} + {0} = {1}", "one", 2) == "one + one = 2");
	assert(format("{0} - {1} = {2}", 3, 2, "one") == "3 - 2 = one");

	bool error = false;
	try 
	{
		auto t = format("{", 1);
	}
	catch(const std::runtime_error&)
	{
		error = true;
	}
	assert(error);

	error = false;
	try
	{
		auto t = format("{a}", 1);
	}
	catch(const std::runtime_error&)
	{
		error = true;
	}
	assert(error);

	error = false;
	try
	{
		auto t = format("{0} hello }", 1);
	}
	catch(const std::runtime_error&)
	{
		error = true;
	}
	assert(error);
	
		error = false;
	try
	{
		auto t = format("{1}", 1);
	}
	catch(const std::runtime_error&)
	{
		error = true;
	}
	assert(error);
	return 0;
}
