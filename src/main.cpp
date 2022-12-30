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
    double **first_table = read_data(argv[1], rows, column);
    
    while(!is_optimality(first_table, rows, column)) {//check basis
        print_table(first_table, rows, column, iteration++);
        calculate_next_table(first_table, rows, column);
    }

    print_table(first_table, rows, column, iteration++);

    std::cout << std::endl << "Answer: X[1] = " << first_table[rows - 3][0] << "\tX[2] = " << first_table[rows - 2][0] << std::endl;
    
    return 0;
}