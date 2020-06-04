#include <iostream>
#include <cstdlib>
#include "sort.h"
#include <cmath>

void FileCreater()
{
	size_t n = 0x800000;
	std::ofstream input("input.txt", std::ios::binary);
	for (size_t i = 0; i < n; ++i)
	{
		uint64_t x = rand();
		input.write(reinterpret_cast<char*>(&x), sizeof(uint64_t));
	}
	input.close();
}

int main()
{    
	FileCreater();

	sortFile();

	std::ifstream output ("output.txt", std::ios::binary);
	uint64_t prev, next;
	output.read(reinterpret_cast<char*>(&prev), sizeof(uint64_t));
	while(!output.eof())
	{
		output.read(reinterpret_cast<char*>(&next), sizeof(uint64_t));
		if (prev > next)
		{
			std::cout << "\tBad sort "<< std::endl;
			break;
		}
		prev = next;
	}
	output.close();
	
	return 0;
}
