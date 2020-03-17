#include "functions.h"

void parser(const std::string &s, onPart onStart, onPart onEnd,
			typeNumber onNumber, 
			typeText onText
			)
{
	onStart();
	std::stringstream ss(s);
	std::string str;
	while (ss >> str)
	{
		if (digit(str))
			onNumber(create_num(str));
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

int create_num(const std::string &s)
{
    int num = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        num = num*10 + (s[i]-'0');
    }
    return num;
}

