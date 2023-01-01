#include <iostream>
#include <filesystem>

#include "function.h"

int main(int argc, char **argv ){
    if(argc < 2) { // check arguments
        std::cerr << "Dont have path" << std::endl;
        return 0;
    }

    if(!std::filesystem::exists(argv[1])) {
        std::cerr << "Bad file" << std::endl;
        return 0;
    }

    //read data from file
    int rows, column, iteration = 0;
    double **table = read_data(argv[1], rows, column);
    
    while(!is_optimality(table, rows, column)) {//check basis
        print_table(table, rows, column, iteration++);
        calculate_next_table(table, rows, column);
    }

    print_table(table, rows, column, iteration++);

    std::cout << std::endl << "Answer: X[1] = " << table[rows - 3][0] << "\tX[2] = " << table[rows - 2][0] << std::endl;
    
    return 0;
}