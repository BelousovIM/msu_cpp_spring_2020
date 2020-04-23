#include "functions.h"

#include <vector>
#include <cassert>

template<typename T>
void assert_equals(const Vector<T>& myVec, const std::vector<T> Vec) 
{
	assert (myVec.size() == Vec.size());

	for (size_t i = 0; i < Vec.size(); ++i) 
	{
		assert(Vec[i] == myVec[i]);
	}
}

int main()
{
    Vector<int> myVec = {100, 100, 700};
    std::vector<int> Vec = {100, 100, 700};
    assert_equals(myVec, Vec);
    
	
	myVec.pop_back();
    myVec.push_back(100);
    Vec.pop_back();
    Vec.push_back(100);
    assert_equals(myVec, Vec);

	for (auto i = myVec.begin(); i != myVec.end(); ++i) 
	{
		assert(*i == 100);
	}
	
	for (auto i = myVec.rbegin(); i != myVec.rend(); ++i) 
	{
		assert(*i == 100);
	}
	
    myVec.clear(); 
    Vec.clear();
    assert(myVec.size() == Vec.size());
    return 0;
}
