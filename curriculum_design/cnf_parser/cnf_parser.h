//
//  cnf_parser.h
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/3.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#ifndef cnf_parser_h
#define cnf_parser_h

#include "../my_cnf_struct.h"

void create_cnf_node(root* proot, lit_number temp_lit, clause_number clause_count);
/*
 * Function Name: create_cnf_node
 * Module: cnf_parser
 * Parameter: root*, lit_number, clause_number
 * Return: void
 * Use: create cnf node
 */

fun_status load_cnf(root* proot);
/*
 * Function Name: load_cnf
 * Module: cnf_parser
 * Parameter: root*
 * Return: fun_status
 * Use: load the cnf file to memory
 */

fun_status save_cnf(root* proot);
/*
 * Function Name: save_cnf
 * Module: cnf_parser
 * Parameter: root*
 * Return: fun_status
 * Use: save the cnf from memory to file
 */

fun_status print_cnf(root* proot);
/*
 * Function Name: print_cnf
 * Module: cnf_parser
 * Parameter: root*
 * Return: fun_status
 * Use: print the cnf to stdout
 */

#endif /* cnf_parser_h */
