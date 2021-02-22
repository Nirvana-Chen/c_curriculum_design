//
//  my_sudoku_struct.h
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/20.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#ifndef my_sudoku_struct_h
#define my_sudoku_struct_h

#include "../my_cnf_struct.h"

typedef struct node {
    lit_number lit;             //cnf lit
    int square_number;          //actual number
    struct node* lit_node;      //link list
}node;

typedef struct square {
    int exist_status;           //number in the square, PENDING: active
    int available_num;          //if status is PENDING, available number
    node* lit_node;             //point to link list for lit node
}square;

typedef struct sudoku_root {
    int holes;                  //holes in the grid
    lit_number lit_num;         //cnf literal number
    clause_number clau_num;     //cnf clause number
    square grid[10][10];        //9*9 grid info
    square row[10][10];         //row info
    square column[10][10];      //column info
    square box[10][10];         //3*3 box info
    root* cnf_root;             //point to cnf
    char* cnf_file_name;
}sudoku_root;

void initialize_sudoku_root(sudoku_root* su_root);
/*
 * Function Name: initialize_sudoku_root
 * Module: my_sudoku_struct
 * Parameter: sudoku_root*
 * Return: void
 * Use: initialize the sudoku root
 */

void initialize_sudoku_square(sudoku_root* su_root);
/*
 * Function Name: initialize_sudoku_square
 * Module: my_sudoku_struct
 * Parameter: sudoku_root*
 * Return: void
 * Use: initialize the sudoku square
 */

void free_sudoku_square(sudoku_root* su_root);
/*
 * Function Name: free_sudoku_square
 * Module: my_sudoku_struct
 * Parameter: sudoku_root*
 * Return: void
 * Use: free the sudoku square
 */

extern int random_time;

#endif /* my_sudoku_struct_h */
