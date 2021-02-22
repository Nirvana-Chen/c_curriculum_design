//
//  solver.h
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/3.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#ifndef solver_h
#define solver_h

#include "../my_cnf_struct.h"

//#define INI_ALGORITHM   //use marco to choose algorithm
//#define DEBUG_DPLL
//#define NEW_ONE
#define NEW_TWO

#ifdef DEBUG_DPLL
#include "../cnf_parser/cnf_parser.h"
#endif

fun_status dpll(root* proot);
/*
 * Function Name: dpll
 * Module: solver
 * Parameter: root*
 * Return: fun_status (TRUE: sat; FALSE: unsat)
 * Use: use dpll algorithm to slove the sat and output the result to file
 */

fun_status dpll_main(root* proot);
/*
 * Function Name: dpll_main
 * Module: solver
 * Parameter: root*
 * Return: fun_status (TRUE: sat; FALSE: unsat)
 * Use: use dpll algorithm to slove the sat problem
 */

fun_status is_unit_clause(clauses* pclause);
/*
 * Function Name: is_unit_clause
 * Module: solver
 * Parameter: clauses*
 * Return: fun_status (TRUE: is unit clause; FALSE: no)
 * Use: check the clauses to get a unit clause
 */

clause_number have_unit_clause(root* proot);
/*
 * Function Name: have_unit_clause
 * Module: solver
 * Parameter: root*
 * Return: clause_number (0 means no unit clause)
 * Use: check the clauses to get a unit clause
 */

lit_number decide(root* proot);
/*
 * Function Name: decide
 * Module: solver
 * Parameter: root*
 * Return: lit_number
 * Use: choose a suitable lit
 */

fun_status bcp(root* proot, lit_number plit);
/*
 * Function Name: bcp
 * Module: solver
 * Parameter: root*, lit_number
 * Return: fun_status (OK: succeed; ERROR: confilct exists)
 * Use: use unit clause rulr to bcp deduce to simplify the clauses
 */

fun_status bcp_deduce(root* proot, lit_number plit);
/*
 * Function Name: bcp_deduce
 * Module: solver
 * Parameter: root*, lit_number
 * Return: fun_status (OK: succeed; ERROR: confilct exists)
 * Use: father function of bcp, switch case
 */

void conflict_analysis(root* proot);
/*
 * Function Name: conflict_analysis
 * Module: solver
 * Parameter: root*
 * Return: void
 * Use: check conflicts in proot and analyse
 */

lit_number back_track(root* proot, lit_number plit);
/*
 * Function Name: back_track
 * Module: solver
 * Parameter: root*, lit_number
 * Return: lit_number
 * Use: back track to select the conflicting lit
 */

void reset_bcp(root* proot, lit_number plit);
/*
 * Function Name: reset_bcp
 * Module: solver
 * Parameter: root*, lit_number
 * Return: void
 * Use: reset the clauses to plit step
 */

void output_to_file(root* proot, fun_status sat_status);
/*
 * Function Name: output_to_file
 * Module: solver
 * Parameter: root*, fun_status
 * Return: void
 * Use: output the results to file_path
 */

void output_to_stdout(root* proot, fun_status sat_status);
/*
 * Function Name: output_to_stdout
 * Module: solver
 * Parameter: root*, fun_status
 * Return: void
 * Use: output the results to stdout
 */

fun_status res_file_check(root* proot);
/*
 * Function Name: res_file_check
 * Module: solver
 * Parameter: root*
 * Return: fun_status (TRUE; FALSE)
 * Use: check the res file
 */

fun_status output_check(root* proot);
/*
 * Function Name: output_check
 * Module: solver
 * Parameter: root*
 * Return: fun_status (TRUE; FALSE)
 * Use: check the output after dpll
 */

#endif /* solver_h */
