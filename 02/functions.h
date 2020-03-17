#pragma once
#include <cstdlib>
#include <iostream> 
#include <string>
#include <sstream>
#include <ctype.h>
#include <functional> 
#include <vector>

using onItem = std::function<void(const std::string &)>;
using onPart = std::function<void()>;



void parser(const std::string &, onPart onStart = [](){}, 
			onPart onEnd = [](){},
			onItem onNumber = [](const std::string &){},
			onItem onText = [](const std::string &){});

bool digit(const std::string &);
bool alpha(const std::string &);
