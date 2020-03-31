#include "functions.h"

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
	auto str = std::stringstream("123 true 127");
	Deserializer deserializer(str);
	assert (deserializer.load(y) == Error::NoError);

	assert(y.a == 123);
	assert(y.b == true);
	assert(y.c == 127);

	//------------------------------------------------------------------
	auto str = std::stringstream("");
	Deserializer deserializer(str);
	assert (deserializer.load(y) == Error::CorruptedArchive);

	//------------------------------------------------------------------
	auto str = std::stringstream("123");
	Deserializer deserializer(str);
	assert (deserializer.load(y) == Error::CorruptedArchive);

	//------------------------------------------------------------------
	auto str = std::stringstream("123 true mother");
	Deserializer deserializer(str);
	assert (deserializer.load(y) == Error::CorruptedArchive);

	//------------------------------------------------------------------
	auto str = std::stringstream("123 false 129 130");
	Deserializer deserializer(str);
	assert (deserializer.load(y) != Error::CorruptedArchive);
	assert(y.a == 123);
	assert(y.b == false);
	assert(y.c == 129);

	return 0;
}
