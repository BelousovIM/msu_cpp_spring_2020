#pragma once
#include <iostream>
#include <cassert>
#include <sstream>
#include <cstdio>
#include <vector>
#include <string>
#include <cctype>

#include <exception>


template<class T>
void get_params(std::vector<std::string>& array, T&& arg)
{
	std::stringstream stream;
	stream << arg;
	array.push_back(stream.str());
}

template<class T, class... ArgsT>
void get_params(std::vector<std::string>& array, T&& arg, ArgsT&&... args)
{
	std::stringstream stream;
	stream << arg;
	array.push_back(stream.str());
	get_params(array, std::forward<ArgsT>(args)...);
}

template <class... ArgsT>
std::string format(const std::string& s, ArgsT&&... args)
{
	std::vector<std::string> params;
	get_params(params, std::forward<ArgsT>(args)...);
	std::stringstream answer;
	for(size_t i = 0; i<s.size(); ++i)
	{

		if(s[i] == '}')
		{
			throw std::runtime_error("Extra close brace");
		}
		if(s[i] == '{')
		{
			size_t num = 0;
			++i;
			for(; std::isdigit(s[i]); ++i)
			{

				num = num*10 + s[i] - '0';
			}


			if (s[i] != '}')
			{
				throw std::runtime_error("Close brace");
			}
			if(num >= params.size())
			{
				throw std::runtime_error("Correct data in brace");
			}
			answer << params[num];

		}
		else
		{
			answer << s[i];
		}
	}

	return answer.str();
}

