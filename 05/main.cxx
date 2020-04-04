#include "functions.h"

main()
{
	int N = 100;
	for (int i = 0; i < N; ++i)
	{
		long long x_r = rand()%(int)1e9;
		long long y_r = rand()%(int)1e9;
		x_r = rand()%2 == 1 ? x_r : -1 * x_r;
		y_r = rand()%2 == 1 ? y_r : -1 * y_r;
		BigInt A(x_r);
		BigInt B(y_r);
		assert(A + B == x_r + y_r);
		assert(A - B == x_r - y_r);
		assert((A == B) == (x_r == y_r));
		assert((A != B) == (x_r != y_r));
		assert(A > B == x_r > y_r);
		assert(A >= B == x_r >= y_r);
		assert(A < B == x_r < y_r);
		assert(A <= B == x_r <= y_r);
		assert(-A == -x_r);
		assert(-B == -y_r);

		std::stringstream out1;
		std::stringstream out2;
		out1 << A;
		out2 << x_r;
		assert(out1.str() == out2.str());
		
	}

	return 0;	
}
