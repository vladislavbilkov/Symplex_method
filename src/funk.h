#pragma once

#include <stdio.h>
#include <stdlib.h>

int size_row(char *input)
{
    int row = 1;
    
    for(int i = 0; input[i] != '\0'; i++)
    {
		if(input[i] == '\n')
		{
			row++;
		}
    }

	return row;
}

int size_column(char *input)
{
    int max_s = 0, max_x = 0;
	for(size_t i = 0; input[i] != '\0'; i++)
	{
		if(input[i] == 'x' && (input[i + 1] - 48) > max_x)
		{
			max_x = (input[i + 1] - 48);
		}

		if(input[i] == 'S' && (input[i + 1] - 48) > max_s)
		{
			max_s = (input[i + 1] - 48);
		}
	}
    return max_s + 1 + max_x;
}

int max_x(char *input)
{
    int max_x = 0;

    for(size_t i = 0; input[i] != '\0'; i++)
	{
		if(input[i] == 'x' && (input[i + 1] - 48) > max_x)
		{
			max_x = (input[i + 1] - 48);
		}
    }

    return max_x;
}

void initial_table(char *input, int row, int column, double matr[row][column])
{
    //визначення розмірів матриці
    int maxx = max_x(input);
    int isfirst = 1;
    for(int i = 0, j = row - 1; input[i] != '\0'; i++)
    {
        if(input[i] == 'x')
        {
            if(input[i - 1] == '\n')
            {
                matr[j][(input[i + 1] - 48)] = 1;
                continue;
            }

            if(input[i - 1] == ' ')
            {
                if(input[i - 2] == '-')
                {
                    matr[j][(input[i + 1] - 48)] = -1;
                    continue;
                }
                matr[j][(input[i + 1] - 48)] = 1;
                continue;
            }

            if(input[i - 3] == '-')
            {
                matr[j][(input[i + 1] - 48)] = - (input[i - 1] - 48);
                continue;
            }

            matr[j][(input[i + 1] - 48)] = input[i - 1] - 48;
            continue;
        }
        if(input[i] == 'S')
        {
            if(input[i - 1] == '\n')
            {
                matr[j][(input[i + 1] - 48) + maxx] = 1;
                continue;
            }

            if(input[i - 1] == ' ')
            {
                if(input[i - 2] == '-')
                {
                    matr[j][(input[i + 1] - 48) + maxx] = -1;
                    continue;
                }
                matr[j][(input[i + 1] - 48) + maxx] = 1;
                continue;
            }

            if(input[i - 3] == '-')
            {
                matr[j][(input[i + 1] - 48) + maxx] = - (input[i - 1] - 48);
                continue;
            }

            matr[j][(input[i + 1] - 48) + maxx] = input[i - 1] - 48;
            continue;
        }
        if(input[i] == '=')
        {
            char tmp[5];

            for(int j = 1, c = 0; input[i + j] != '\0'; j++)
            {
                if(input[i + j] == '\n')
                {break;}
                if(input[i + j] == ' ')
                {continue;}
                tmp[c++] = input[i + j];
            }

            matr[j][0] = atoi(tmp);
        }
        if(input[i] == '\n')
        {
            if(isfirst == 1)
            {
                j = 0;
                isfirst = 0;
                continue;
            }
            j++;
        }
    }
}

int is_optimality(int row, int column, double matr[row][column]) {
    for(int i = 0; i < column; i++) {
        if(matr[row - 1][i] < 0) {
            return 0;
        }
    }
    return 1;
}

int find_main_row(int row, int column, double matr[row][column], int main_column) {
    double tmp_mas[row - 1];
    
    for(int i = 0; i < row - 1; i++) {
        tmp_mas[i] = matr[i][0] / matr[i][main_column];
    }

    int index = 0, minel = tmp_mas[0];
    
    for(int i = 1; i < row - 1; i++) {
        if(tmp_mas[i] > 0 && minel > tmp_mas[i]) {
            index = i;
            minel = tmp_mas[i];
        }
    }
    return index;
}

int find_main_column(int row, int column, double matr[row][column]) {
    int index = 1, minel = matr[row - 1][1];
    
    for(int i = 1; i < column - 1; i++) {
        if(minel > matr[row - 1][i + 1]) {
            index = i + 1;
            minel = matr[row - 1][i + 1];
        }
    }
    return index;
}

void calculate_next_table(int row, int column, double matr[row][column]) {
    int main_column = find_main_column(row, column, matr);
    int main_row = find_main_row(row, column, matr, main_column);
    
    double last_matr[row][column];

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            last_matr[i][j] = 0;
        }
    }

    //calculate next table main row
    for(int i = 0; i < column; i++) {
        last_matr[main_row][i] = matr[main_row][i] / matr[main_row][main_column];
    }
    
    //calculate next table
    for(int i = 0; i < row; i++) {
        if(i == main_row) continue;
        for(int j = 0; j < column; j++) {
            last_matr[i][j] = matr[i][j] - (matr[i][main_column] * matr[main_row][j]);
        }
    }

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            matr[i][j] = last_matr[i][j];
        }
    }
}