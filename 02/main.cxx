#include "functions.h"

// переменные для теста 
static int max_length;
static int n_count;
static int w_count;
static bool t_start;
static bool t_end;
static bool t_num;
static bool t_word;
static std::string simbol;

// индикатор входа (колбэк)
void is_started()
{
	t_start = true;
}
// индикатор выхода (колбэк)
void is_ended()
{
	t_end = true;
}
// индикатор запуска счетчика и количество чисел (колбэк)
void N_counter(const std::string s)
{
	t_num = true;
	n_count++;
}
// индикатор запуска счетчика и количество слов (колбэк)
void W_counter(const std::string s)
{
	t_word = true;
	w_count++;
}
// максимальная длина и слово/число максимальной длины (колбэк)
void length(const std::string s)
{
	if (s.size() > max_length)
	{
		max_length = s.size();
		simbol = s;
	}
}
int main()
{
	t_start = false;
	t_end = false;
	
	parser("1 a 2 b 3 c 4 d 5 e 12 ab 23 bc 34 cd 45 de 123 abc",
	is_started, is_ended);
	if (!t_start or !t_end)
	{
		std::cout << "BAD1" << std::endl;
		return 1;
	}
    
	//------------------------------------------------------------------
	t_start = false;
	t_end = false;
	t_num = false;
	t_word = false;
	n_count = 0;
	w_count = 0;
	
	parser("1 a 2 b 3 c\n 4 d 5e 12 \nab 23 bc 34 cd\t 45de 123 abc",
	is_started, is_ended, N_counter, W_counter);
	if (!t_start or !t_end or !t_num or !t_word or
		n_count!= 8 or w_count!= 8)
	{
		std::cout << "BAD2" << std::endl;
		return 1;
	}
	
	//------------------------------------------------------------------
	t_start = false;
	t_end = false;
	t_num = false;
	t_word = false;
	n_count = 0;
	w_count = 0;
	
	parser("123\n\t abc rac 1\n\n 4 5 dfg",
	is_started, [](){}, [](const std::string){}, W_counter);
	if (!t_start or t_end or t_num or !t_word or 
		n_count!= 0 or w_count!= 3)
	{
		std::cout << "BAD3" << std::endl;
		return 1;
	}
	
	//------------------------------------------------------------------
	t_start = false;
	max_length = 0;
	simbol = "";
    
	parser("123 abc rac 1 4 5 dfg abcdefg\t 43abcdefg123",
	is_started, [](){}, length, length);
	if (!t_start or max_length!=7 or simbol!="abcdefg" )
	{
		std::cout << "BAD4" << std::endl;
		return 1;
	}

	std::cout<< "ALL TESTS ARE SUCCESFULL" << std::endl;

	return 0;
}
