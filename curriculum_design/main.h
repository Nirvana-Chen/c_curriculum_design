//
//  main.h
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/3.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#ifndef main_h
#define main_h

#include "cnf_parser/cnf_parser.h"
#include "solver/solver.h"
#include "sudoku/sudoku.h"

//#define TEST_SOLVER
//#define TEST_SUDOKU

fun_status menu_main(void);
/*
 * Function Name: menu_main
 * Module: main
 * Parameter: void
 * Return: fun_status
 * Use: print main menu
 */

void sat_solver(root* proot);
/*
 * Function Name: dpll
 * Module: main
 * Parameter: root*
 * Return: void
 * Use: sat_solver main
 */

fun_status menu_sat(void);
/*
 * Function Name: menu_sat
 * Module: main
 * Parameter: void
 * Return: fun_status
 * Use: print sat menu
 */

void sudoku(sudoku_root* su_root);
/*
 * Function Name: initialize_sudoku_root
 * Module: main
 * Parameter: sudoku_root*
 * Return: void
 * Use: sudoku main
 */

fun_status menu_sudoku(void);
/*
 * Function Name: menu_sudoku
 * Module: main
 * Parameter: void
 * Return: fun_status
 * Use: print sudoku menu
 */

#endif /* main_h */
