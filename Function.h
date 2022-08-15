#ifndef FUNCTION
#define FUNCTION

#define Test

#include <iostream>
#include <string>
#include <cstdio>

bool check_base_str(std::string input);
bool check_limitation_str(std::string input);
std::string add_balance_temp(std::string& input_base, std::string input_limitation);
double** initial_table(std::string input_base, std::string input, int& size_i, int& size_j);
double* get_control_varible(double* matr[], const int size_i, const int size_j, int &index);
double* get_Q_items(double* matr[], const int size_i, const int size_j, const int indexmax);
void print_table(double* matr[], const int size_i, const int size_j, double* control_varible, double* Q_items);

#endif // !FUNCTION