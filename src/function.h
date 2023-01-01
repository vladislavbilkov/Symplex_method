#pragma once

#include <fstream>

void get_size_table(int & rows, int & column, std::ifstream &file);

void set_table(const int rows, std::ifstream &file, double **table);

double ** read_data(const char *path, int &rows, int & column);

void print_table(double **table, const int rows, int column, const int iteration);

bool is_optimality(double ** table, const int rows , const int column);

int find_main_row(double ** table, const int rows , const int column, int main_column);

int find_main_column(double ** table, const int rows , const int column);

void calculate_next_table(double ** table, const int rows , const int column);