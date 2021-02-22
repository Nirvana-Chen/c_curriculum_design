//
//  sudoku_creator.h
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/20.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#ifndef sudoku_creator_h
#define sudoku_creator_h

#include "../my_sudoku_struct.h"
#include "../sudoku_io/sudoku_io.h"
#include "../../solver/solver.h"
#include "../sudoku_solver/sudoku_solver.h"

fun_status sudoku_creator(sudoku_root* su_root);
/*
 * Function Name: sudoku_creator
 * Module: sudoku/sudoku_creator
 * Parameter: sudoku_root*
 * Return: fun_status
 * Use: create sudoku
 */

fun_status create_sudoku_ending(sudoku_root* su_root);
/*
 * Function Name: create_sudoku_ending
 * Module: sudoku/sudoku_creator
 * Parameter: sudoku_root*
 * Return: fun_status
 * Use: create sudoku ending
 */

fun_status dig_hole_algorithm(sudoku_root* su_root, int level);
/*
 * Function Name: dig_hole_algorithm
 * Module: sudoku/sudoku_creator
 * Parameter: sudoku_root*, int
 * Return: fun_status
 * Use: use dig hole algorithm to create sudoku from an ending
 */

void initialize_grid(sudoku_root* su_root);
/*
 * Function Name: initialize_grid
 * Module: sudoku/sudoku_creator
 * Parameter: sudoku_root*
 * Return: void
 * Use: set grid exist status 0
 */

fun_status create_row(sudoku_root* su_root, int row);
/*
 * Function Name: create_row
 * Module: sudoku/sudoku_creator
 * Parameter: sudoku_root*, int
 * Return: fun_status
 * Use: father of random_row
 */

fun_status random_row(sudoku_root* su_root, int row);
/*
 * Function Name: random_row
 * Module: sudoku/sudoku_creator
 * Parameter: sudoku_root*, int
 * Return: fun_status
 * Use: create a random row
 */

fun_status check_conflict(sudoku_root* su_root, int row);
/*
 * Function Name: check_conflict
 * Module: sudoku/sudoku_creator
 * Parameter: sudoku_root*, int
 * Return: fun_status
 * Use: check the conflict status of the random row
 */

void random_dig(sudoku_root* su_root, int level);
/*
 * Function Name: random_dig
 * Module: sudoku/sudoku_creator
 * Parameter: sudoku_root*, int
 * Return: void
 * Use: random dig
 */

void jump_dig(sudoku_root* su_root);
/*
 * Function Name: jump_dig
 * Module: sudoku/sudoku_creator
 * Parameter: sudoku_root*
 * Return: void
 * Use: jump_dig
 */

void snake_dig(sudoku_root* su_root);
/*
 * Function Name: snake_dig
 * Module: sudoku/sudoku_creator
 * Parameter: sudoku_root*
 * Return: void
 * Use: snake_dig
 */

void sequence_dig(sudoku_root* su_root);
/*
 * Function Name: sequence_dig
 * Module: sudoku/sudoku_creator
 * Parameter: sudoku_root*
 * Return: void
 * Use: sequence_dig
 */

fun_status rule_conflict(sudoku_root* su_root, int t, int i, int j);
/*
 * Function Name: check_conflict
 * Module: sudoku/sudoku_creator
 * Parameter: sudoku_root*, int, int, int
 * Return: fun_status
 * Use: check the conflict status of dig hole
 */

fun_status sudo_solvable(sudoku_root* su_root);
/*
 * Function Name: sudo_solvable
 * Module: sudoku/sudoku_creator
 * Parameter: sudoku_root*
 * Return: fun_status
 * Use: check if the sudoku solvable
 */

#endif /* sudoku_creator_h */
