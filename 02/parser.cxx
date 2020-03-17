#include "functions.h"

void parser(const std::string &s, onPart onStart, onPart onEnd,
			onItem onNumber, onItem onText
			)
{
	onStart();
	std::stringstream ss(s);
	std::string str;
	while (ss >> str)
	{
		if (digit(str))
			onNumber(str);
		else if (alpha(str))
			onText(str);
	}
	onEnd();
}

bool digit(const std::string &s)
{
	int i = 0;
	while(s[i])
		if (!isdigit(s[i++]))
			return false;

	return true;
}
bool alpha(const std::string &s)
{
	int i = 0;
	while(s[i])
		if (!isalpha(s[i++]))
			return false;

	return true;
}

