#include "function.h"
#include <iostream>
#include <string>

void get_size_table(int & rows, int & column, std::ifstream &file) {
    std::string lastline;
    while(getline(file, lastline)) {
        rows++;
    }

    for(int i = 0; i < lastline.size(); i++) {
        if(lastline[i] == ' ') {
            column++;
        }
    }
    column++;
}

void set_table(const int rows, std::ifstream &file, double **table) {
    file.clear(); //reset flag
    file.seekg(0, std::ios::beg);

    for(int i = 0; i < rows; i++) {
        std::string str, tmp;
        getline(file, str);
        int k = 0;
        for(int j = 0; j < str.size(); j++) {
            if(str[j] == ' ' || str[j] == '\t') {
                table[i][k] = std::stold(tmp);
                k++;
                tmp = "";
                continue;
            }
            tmp += str[j];
        }
        table[i][k] = std::stold(tmp);
    }
}

double ** read_data(const char *path, int &rows, int & column) {
    std::ifstream data(path);
    
    if(!data){
        std::cerr << "File not opened" << std::endl;
        return NULL;
    }
    
    //get size table
    rows = 0, column = 0;
    get_size_table(rows, column, data);
    
    double ** table = new double*[rows];
    
    for(int i = 0; i < rows; i++) { //create table
        table[i] = new double[column]; 
    }
    
    //set table
    set_table(rows, data, table);
    data.close();
    return table;
}

void print_table(double**table, const int rows, int column, const int iteration) {
    std::cout << "\n" << iteration << " - iteration" << std::endl << "members\t";
    for(int i = 1; i < column; i++) {
        std::cout << "X" << i << "\t";
    }
    std::cout << std::endl;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < column; j++) {
            std::cout << table[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

bool is_optimality(double ** table, const int rows, const int column) {
    for(int i = 0; i < column; i++) {
        if(table[rows - 1][i] < 0) {
            return false;
        }
    }
    return true;
}

void calculate_next_table(double ** table, const int rows , const int column) {
    int main_column = find_main_column(table, rows, column);
    int main_row = find_main_row(table, rows, column, main_column);
    
    double ** new_table = new double*[rows];
    
    for(int i = 0; i < rows; i++) { //create table
        new_table[i] = new double[column]; 
    }

    //calculate next table main row
    for(int i = 0; i < column; i++) {
        new_table[main_row][i] = table[main_row][i] / table[main_row][main_column];
    }

    //calculate next table
    for(int i = 0; i < rows; i++) {
        if(i == main_row) continue;
        for(int j = 0; j < column; j++) {
            new_table[i][j] = table[i][j] - (table[i][main_column] * new_table[main_row][j]);
        }
    }

    for(int i = 0; i < rows; i++) {
        delete table[i];
        table[i] = new_table[i]; 
    }
    table = new_table;
}

int find_main_row(double ** table, const int rows , const int column, int main_column) {
    double tmp_mas[rows - 1];
    
    for(int i = 0; i < rows - 1; i++) {
        tmp_mas[i] = table[i][0] / table[i][main_column];
    }

    int index = 0, minel = tmp_mas[0];
    
    for(int i = 1; i < rows - 1; i++) {
        if(tmp_mas[i] > 0 && minel > tmp_mas[i]) {
            index = i;
            minel = tmp_mas[i];
        }
    }
    return index;
}

int find_main_column(double ** table, const int rows , const int column) {
    int index = 1, minel = table[rows - 1][1];
    
    for(int i = 1; i < column - 1; i++) {
        if(minel > table[rows - 1][i + 1]) {
            index = i + 1;
            minel = table[rows - 1][i + 1];
        }
    }
    return index;
}