#include "functions.h"

main()
{
	const int rows = 5;
	const int columns = 7;

	Matrix X(rows, columns);
    
	if (X.getRows() != 5 or X.getColumns() != 7)
	{
		std::cout << "BAD1" << std::endl;
		return 1;
	}
	
	//------------------------------------------------------------------
	for(int i=0; i < X.getRows(); ++i)
		for(int j=0; j < X.getColumns(); ++j)
			X[i][j] = 3;

    X *= 5;

	for(int i=0; i < X.getRows(); ++i)
		for(int j=0; j < X.getColumns(); ++j)
			if(X[i][j] != 15)
			{
				std::cout << "BAD2" << std::endl;
				return 1;
			}
			
	//------------------------------------------------------------------
	Matrix A(rows, columns), B(rows, columns);
	for(int i=0; i < A.getRows(); ++i)
		for(int j=0; j < A.getColumns(); ++j)
		{
			A[i][j] = 15;
			B[i][j] = 123;
		}

	if(X!=X or X!=A or X==B)
	{
		std::cout << "BAD3" << std::endl;
		return 1;
	}
	
	//------------------------------------------------------------------
	bool ind = false;
    try
    {
        X[123][123];
    }

    catch(const std::out_of_range& out_of_rage)
    {
        ind = true;
    }
    
    if(!ind)
	{
		std::cout << "BAD4" << std::endl;
		return 1;
	}
	
    std::cout << "ALL TESTS ARE SUCCESFULL" << std::endl;
    return 0;
}
