#include "Function.h"

bool check_base_str(std::string input) {
	const int length = 10;
	std::string tmp[length];
	int index = 0, j = 0;
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == '+' || input[i] == '-')
		{
			tmp[j++] = input.substr(index, i - 1);
			index = i + 1;
		}
		if (input[i] == '=')
		{
			tmp[j++] = input.substr(index, i - 2);
			index = i + 1;
		}
		if (i + 1 == input.length())
		{
			tmp[j++] = input.substr(index, i);
		}
	}
	for (size_t i = 0; i < j; i++)
	{
		int k = tmp[i].find('x');
		if (k != -1)
		{
			if (tmp[k + 1] > "0")
			{
				return false;
			}
			k = -1;
		}
		else
		{
			if (tmp[i] >= "0") {
				return false;
			}
		}
	}
	return true;
}

bool check_limitation_str(std::string input) {
	const int length = 10;
	std::string tmp[length];
	int index = 0, j = 0;
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == '\n')
		{
			tmp[j++] = input.substr(index, i - 1);
			index = i + 1;
		}
	}
	for (size_t i = 0; i < j; i++)
	{
		if (check_base_str(tmp[i]) == false) {
			return false;
		}
	}
	return true;
}

std::string add_balance_temp(std::string& input_base, std::string input) {
	std::string tmp[10];
	int indexj = 0, weight = 0;
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == char(10)) {
			tmp[indexj] = input.substr(weight, i - weight);
			std::string tmp_str = " + 1S";
			tmp_str += char(49 + indexj);
			tmp[indexj].insert(tmp[indexj].find('<') - 1, tmp_str);
			weight = i + 1;
			indexj++;
		}
	}
	std::string ret_str;
	for (size_t i = 0; i < indexj; i++)
	{
		ret_str += tmp[i] + '\n';
		input_base += " + 0S";
		input_base += char(49 + i);
	}
	return ret_str;
}

double** initial_table(std::string base, std::string input, int& size_i, int& size_j) {
	//initial matr
	size_j = (char(base[base.find_last_of('S') + 1]) - 49) + 2;
	size_i = (char(base[base.find_last_of('x') + 1]) - 49) + size_j + 2;
	double** matr = new double* [size_j];
	for (size_t i = 0; i < size_j; i++)
	{
		matr[i] = new double[size_i] {};
	}

	//fill table
	int tmpj = 1, tmpi = 1, index = 0;
	for (size_t i = 0; i < base.length(); i++)
	{
		if (base[i] == 'x' || base[i] == 'S' || i == base.length()) {
			index = base.find_last_of('+', i);
			matr[0][tmpj++] = std::atoi(base.substr(index + 1, i - index - 1).c_str());
		}
	}

	tmpj = 1, index = -1;
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == 'x')
		{
			if (tmpj != 0)
			{
				index = input.find_last_of('+', i);
			}
			matr[tmpi][tmpj++] = std::atoi(input.substr(index + 1, (i - index) - 1).c_str());
		}
		if (input[i] == 'S')
		{
			index = input.find_last_of('+', i);
			int tmp = input.find_first_of('=', i);
			tmpj += std::atoi(input.substr(i + 1, (i - tmp) - 1).c_str()) - 1;
			matr[tmpi][tmpj] = std::atoi(input.substr(index + 1, (i - index) - 1).c_str());
			tmpj = 1;
		}
		if (input[i] == '\n' || input[i] == '\0')
		{
			index = input.find_last_of('=', i);
			matr[tmpi++][size_i - 1] = std::atoi(input.substr(index + 1, i - index - 1).c_str());
			index = i;
		}
	}
	return matr;
}

double* get_control_varible(double* matr[], const int size_i, const int size_j, int &index) {
	double* mas = new double[size_i - 2];

	for (size_t i = 1; i < size_i - 1; i++)
	{
		mas[i - 1] = 0;
		for (size_t j = 1; j < size_j; j++)
		{
			mas[i - 1] += matr[j][i] * matr[j][0];
		}
		mas[i - 1] -= matr[0][i];
	}

	int max = 1245151; index = -1;
	for (size_t i = 0; i < size_i - 2; i++)
	{
		if (mas[i] < 0 && mas[i] < max)
		{
			max = mas[i];
			index = i;
		}
	}

	return mas;
}

double* get_Q_items(double* matr[], const int size_i, const int size_j, const int indexmax) {
	double* mas = new double[size_j - 2];
	for (size_t i = 0; i < size_j; i++)
	{
		mas[i] = matr[i][size_i - 1] / matr[i][indexmax + 1];
	}

	int max = 1245151, index = 0;
	for (size_t i = 0; i < size_i - 1; i++)
	{
		if (mas[i] > 0 && mas[i] < max)
		{
			max = mas[i];
			index = i;
		}
	}
	return mas;
}

void print_table(double* matr[], const int size_i, const int size_j, double* control_varible, double* Q_items) {
	for (size_t i = 0; i < size_j; i++)
	{
		for (size_t j = 0; j < size_i; j++)
		{
			std::cout << matr[i][j] << "\t";
		}
		if (i > 0 && i < size_i - 1)
		{
			std::cout << Q_items[i];
		}
		std::cout << std::endl;
	}
	std::cout << "\t";
	for (size_t i = 0; i < size_i - 2; i++)
	{
		std::cout << control_varible[i] << "\t";
	}
}