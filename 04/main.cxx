#include "functions.h"


struct Data
{
	uint64_t a;
	bool b;
	uint64_t c;

	Data(uint64_t a, bool b, uint64_t c)
		: a(a)
		, b(b)
		, c(c)
	{
	}

	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c);
	}

	template <class Deserializer>
	Error deserialize(Deserializer& deserializer)
	{
		return deserializer(a, b, c);
	}
};


int main()
{
    Data x(15, true, 54);
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);
    Data y(0, false, 0);
    Deserializer deserializer(stream);
	assert(deserializer.load(y) == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    
	//------------------------------------------------------------------
    y = {0, true, 0};
    auto str1 = std::stringstream("123 true 127");
    Deserializer d1(str1);
    assert (d1.load(y) == Error::NoError);

    assert(y.a == 123);
    assert(y.b == true);
    assert(y.c == 127);
    
	//------------------------------------------------------------------
    auto str2 = std::stringstream("");
    Deserializer d2(str2);
    assert (d2.load(y) == Error::CorruptedArchive);
    
	//------------------------------------------------------------------
    auto str3 = std::stringstream("123 true mother");
    Deserializer d3(str3);
    assert (d3.load(y) == Error::CorruptedArchive);
    
	//------------------------------------------------------------------
    auto str4 = std::stringstream("123 false 129 130");
    Deserializer d4(str4);
    assert (d4.load(y) != Error::CorruptedArchive);
    
	//------------------------------------------------------------------
    auto str5 = std::stringstream("1000 1");
    Deserializer d5(str5);
    assert (d5.load(y) == Error::CorruptedArchive);

    return 0;
}
