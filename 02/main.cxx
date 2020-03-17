#include "functions.h"

int create_num(const std::string &s)
{
    int num = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        num = num*10 + (s[i]-'0');
    }
    return num;
}

int main()
{
	int t_start = false;
	int t_end = false;
	auto is_started = [&t_start](){t_start = true;};
	auto is_ended = [&t_end](){t_end = true;};
	parser("1 a 2 b 3 c 4 d 5 e 12 ab 23 bc 34 cd 45 de 123 abc",
	is_started, is_ended);
	
	if (!t_start or !t_end)
	{
		std::cout << "BAD1" << std::endl;
		return 1;
	}
    
	//------------------------------------------------------------------
	t_start = false;
	int n_count = 0;
	int w_count = 0;
	auto N_counter = [&n_count](const std::string &){n_count++;};
	auto W_counter = [&w_count](const std::string &){w_count++;};
	
	parser("1 a 2 b 3 c\n 4 d 5e 12 \nab 23 bc 34 cd\t 45de 123 abc",
	is_started, [](){}, N_counter, W_counter);
	
	if (!t_start or !t_end or n_count!= 8 or w_count!= 8)
	{
		std::cout << "BAD2" << std::endl;
		return 1;
	}
	
	//------------------------------------------------------------------
	int a = 10;
	int max_length = 0;
	std::string simbol = "";
	auto length = [&max_length, &simbol](const std::string &s)
	{
		if (s.size() > max_length)
		{
			max_length = s.size();
			simbol = s;
		}
	};
	
	parser("123 abc rac 1 4 5 dfg abcdefg\t 43abcdefg123",
	[&a](){a = 4;}, [](){}, length, length);
	
	if (a!=4 or max_length!=7 or simbol!="abcdefg" )
	{
		std::cout << "BAD3" << std::endl;
		return 1;
	}

	//------------------------------------------------------------------
	std::vector<int> v_num;
	int v_test[4] = {123, 1, 4, 5};
	
	parser("123 abc rac 1 4 5 dfg abcdefg\t 43abcdefg123",
	[](){}, [](){}, 
	[&v_num](const std::string &s){v_num.push_back(create_num(s));});
	
	for (int i = 0; i < 4; ++i)
		if (v_num.size()!= 4 or v_num[i]!=v_test[i])
		{
			std::cout << "BAD4" << std::endl;
			return 1;
		}

	std::cout<< "ALL TESTS ARE SUCCESFULL" << std::endl;
	
	return 0;
}
