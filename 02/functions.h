#pragma once
#include <cstdlib>
#include <iostream> 
#include <string>
#include <sstream>
#include <ctype.h>
#include <functional> 
#include <vector>

using onPart = std::function<void()>;
using typeNumber = std::function<void(const int &)>;
using typeText = std::function<void(const std::string &)>;

int create_num(const std::string &);
void parser(const std::string &, onPart onStart = [](){}, 
			onPart onEnd = [](){},
			typeNumber onNumber = [](const int &){},
			typeText onText = [](const std::string &){});

bool digit(const std::string &);
bool alpha(const std::string &);
