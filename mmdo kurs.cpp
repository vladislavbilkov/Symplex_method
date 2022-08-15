#include <iostream>
#include <windows.h>
#include <cstdio>
#include <string>

#include "Function.h"

using namespace std;


int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::cout << "Введіть початковий базис Z= у форматі\nx1 + x2 + xn..." << std::endl;
	std::string str_initial_base, str_limitation;
	//std::getline(std::cin, str_initial_base);
	//check format
	while (false)
	{
		if (check_base_str(str_initial_base))
		{
			std::cout << "Введіть обмеження базис у форматі\nx1 + x2 + xn... <= n\nx1 + x2 +xn... <=n...(для завершення нажміть ESC + Enter)" << std::endl;
			while (std::getchar() != 10)
			{
				std::string tmp_str;
				std::getline(std::cin, tmp_str);
				str_limitation += tmp_str + '\n';
			}
			std::cout << str_limitation;
			break;
		}
		else
		{
			std::cout << "Не вірний ввід даних спробуйте знову" << std::endl;
			std::cout << "Введіть початковий базис Z= у форматі\nx1 + x2 + xn..." << std::endl;
			std::getline(std::cin, str_initial_base);
		}
	}
#ifdef Test
	str_initial_base = "3x1 + 4x2";
	str_limitation = "3x1 + 2x2 <= 12 \n1x1 + 2x2 <= 8 \n5x1 + 0x2 <= 16 \n0x1 + 4x2 <= 12 \n";
	std::cout << str_initial_base << std::endl;
	std::cout << str_limitation << std::endl;
#endif // Test
	str_limitation = add_balance_temp(str_initial_base, str_limitation);
	std::cout << "Запишемо систему в канонічній формі" << std::endl;
	std::cout << str_initial_base << std::endl;
	std::cout << str_limitation << std::endl;
	//create table
	int size_i, size_j, index_control;
	auto matr = initial_table(str_initial_base, str_limitation, size_i, size_j);

	auto control_varible = get_control_varible(matr, size_i, size_j, index_control);
	auto Q_varible = get_Q_items(matr, size_i, size_j, index_control);
	//loop table
	while (index_control > -1) {
		//print
		print_table(matr, size_i, size_j, control_varible, Q_varible);
		//get el
		std::cout << index_control;
		//get new table
		index_control = -1;
		//control and Q varible

	}
	//print end
}
