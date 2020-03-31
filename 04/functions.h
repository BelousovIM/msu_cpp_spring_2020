#pragma once
#include <iostream>
#include <cassert>
#include <sstream>
#include <cstdio>

enum class Error
{
	NoError,
	CorruptedArchive
};

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

class Serializer
{
	
	static constexpr char Separator = ' ';
	std::ostream& out_;
public:

	explicit Serializer(std::ostream& out)
	: out_(out)
	{
	}

	template <class T>
	Error save(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT... args)
	{
		return process(args...);
	}

private:
    
	template <class T>
	Error process(T arg) 
	{
		return saveStream(arg);
	}
	    
	template <class T, class... ArgsT>
	Error process(T arg, ArgsT... args) 
	{
		if (saveStream(arg) != Error::NoError)
		{
			return Error::CorruptedArchive;
		}
		return process(args...);
	}
		
	template <class T>
	Error saveStream(T val)
	{
		if(std::is_same<T, bool>::value)
		{
			if (val)
			{
				out_ << "true" << Serializer::Separator;
			}
			else
			{
				out_ << "false" << Serializer::Separator;
			}
		}
		else if(std::is_same<T, uint64_t>::value)
		{
			out_ << val << Serializer::Separator;
		}
		else
		{
			return Error::CorruptedArchive;
		}
		return Error::NoError;
	}
};

class Deserializer
{
	std::istream& in_;
public:
	explicit Deserializer(std::istream& in)
	: in_(in)
	{
	}

	template <class T>
	Error load(T& object)
	{
		return object.deserialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(std::forward<ArgsT>(args)...);
	}
private:

	template <class T>
	Error loadStream(T& val)
	{
		std::string str;
		in_ >> str;
		if(std::is_same<T, bool>::value)
		{
			if (str == "true")
			{
				val = true;
			}
			else if(str == "false")
			{
				val = false;
			}
			else 
			{
				return Error::CorruptedArchive;
			}
			return Error::NoError;
		}
		else if(std::is_same<T, uint64_t>::value)
		{

			if (str.length() == 0)
			{
				return Error::CorruptedArchive;
			}		
			for (size_t i = 0; i < str.length(); ++i)
			{
				if (!(isdigit(str[i])))
				{
					return Error::CorruptedArchive;
				}
			}
			val = std::stoi(str);
			return Error::NoError;

		}

		return Error::CorruptedArchive;
	}

	template <class T>
	Error process(T&& arg) 
	{
		return loadStream(std::forward<T>(arg));
	}

	template <class T, class... ArgsT>
	Error process(T&& arg, ArgsT&&... args) 
	{
		if (loadStream(std::forward<T>(arg)) != Error::NoError)
		{
			return Error::CorruptedArchive;
		}
		return process(std::forward<ArgsT>(args)...);
	}
};



