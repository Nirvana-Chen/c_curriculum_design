//
//  sudoku_solver.h
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/20.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#ifndef sudoku_solver_h
#define sudoku_solver_h

#include "../my_sudoku_struct.h"
#include "../../cnf_parser/cnf_parser.h"
#include "../../solver/solver.h"

void create_square_lit_node(node* tail, lit_number lit, int square_num);
/*
 * Function Name: create_square_lit_node
 * Module: sudoku/sudoku_solver
 * Parameter: node*, lit_number, int
 * Return: void
 * Use: create square lit node
 */

void lit_correspondence(sudoku_root* su_root);
/*
 * Function Name: lit_correspondence
 * Module: sudoku/sudoku_solver
 * Parameter: sudoku_root*
 * Return: void
 * Use: parse the correspondence between lit and square number in original order
 */

void rcb_correspondence(sudoku_root* su_root);
/*
 * Function Name: rcb_correspondence
 * Module: sudoku/sudoku_solver
 * Parameter: sudoku_root*
 * Return: void
 * Use: parse the correspondence between lit and square number in rows, columns and boxes
 */

void clause_count(sudoku_root* su_root);
/*
 * Function Name: clause_count
 * Module: sudoku/sudoku_solver
 * Parameter: sudoku_root*
 * Return: void
 * Use: work out clause number
 */

fun_status create_cnf(sudoku_root* su_root);
/*
 * Function Name: create_cnf
 * Module: sudoku/sudoku_solver
 * Parameter: sudoku_root*
 * Return: fun_status
 * Use: create cnf
 */

void ascertain_square(sudoku_root* su_root);
/*
 * Function Name: ascertain_square
 * Module: sudoku/sudoku_solver
 * Parameter: sudoku_root*
 * Return: void
 * Use: ascertain square number
 */

#endif /* sudoku_solver_h */
