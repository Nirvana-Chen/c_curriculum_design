//
//  sudoku_io.h
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/20.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#ifndef sudoku_io_h
#define sudoku_io_h

#include "../my_sudoku_struct.h"
#include "../../cnf_parser/cnf_parser.h"

fun_status load_sudoku(sudoku_root* su_root);
/*
 * Function Name: load_sudoku
 * Module: sudoku/sudoku_io
 * Parameter: sudoku_root*
 * Return: fun_status
 * Use: load the sudoku info from cnf file to memory
 */

fun_status save_sudoku(sudoku_root* su_root);
/*
 * Function Name: save_sudoku
 * Module: sudoku/sudoku_io
 * Parameter: sudoku_root*
 * Return: fun_status
 * Use: save the sudoku info and cnf from memory to file
 */

fun_status print_sudoku(sudoku_root* su_root);
/*
 * Function Name: print_sudoku
 * Module: sudoku/sudoku_io
 * Parameter: sudoku_root*
 * Return: fun_status
 * Use: print the sudoku info to stdout
 */

fun_status print_sudoku_cnf(sudoku_root* su_root);
/*
 * Function Name: print_sudoku_cnf
 * Module: sudoku/sudoku_io
 * Parameter: sudoku_root*
 * Return: fun_status
 * Use: print the sudoku cnf to stdout
 */

fun_status save_solution(sudoku_root* su_root);
/*
 * Function Name: save_solution
 * Module: sudoku/sudoku_io
 * Parameter: sudoku_root*
 * Return: fun_status
 * Use: save the sudoku solution from memory to file
 */

fun_status print_solution(sudoku_root* su_root);
/*
 * Function Name: print_solution
 * Module: sudoku/sudoku_io
 * Parameter: sudoku_root*
 * Return: fun_status
 * Use: print the sudoku solution to stdout
 */

#endif /* sudoku_io_h */
