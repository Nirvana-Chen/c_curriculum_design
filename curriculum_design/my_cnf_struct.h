//
//  my_cnf_struct.h
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/3.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#ifndef my_cnf_struct_h
#define my_cnf_struct_h

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <time.h>

//common
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

#define TRUE 1
#define FALSE 0

//for status
#define PENDING 0

//for literals.exist_status
#define PLUS 1
#define MINUS -1
#define BOTH 2

//for literals.visit_status
#define UCR 1               //unit clause rule
#define BCPFIR 2            //bcp deduce first time
#define BCPSEC 3            //bcp deduce second time

//for file_name_parser
#define STRLEN 500

//for changeablity
typedef int fun_status;
typedef int lit_number;
typedef unsigned long clause_number;

extern clause_number step;
extern int algorithm;

typedef struct unit {
    char dpll_status;
    lit_number literal;
    clause_number clause;
    struct unit* lit_unit;
    struct unit* clau_unit;
}unit;

typedef struct literals {
    char exist_status : 4;              //existing status
    char visit_status : 4;              //dpll status
    clause_number clau_count;            //count how many lits
    clause_number visit_order;          //dpll visit order
    unit* lit_unit;
}literals;

typedef struct clauses {
    char dpll_status;                   //dpll status: finished/not finished/fail
    lit_number active_lit_num;          //active lit number
    clause_number visit_order;          //dpll visit order
    unit* clau_unit;                    //pointer to the units
}clauses;

typedef struct root {
    lit_number lit_num;
    clause_number ini_clau_num;
    clause_number stu_clau_num;
    clauses* ini_clau_cnf;
    clauses* stu_clau_cnf;
    literals* literal_cnf;
    double total_time;                  //time count
    char* cnf_file_name;
}root;

char* file_name_parser(void);
/*
 * Function Name: file_name_parser
 * Module: my_cnf_struct
 * Parameter: void
 * Return: char*
 * Use: read file_path from stdin
 */

lit_number abs_lit(lit_number plit);
/*
 * Function Name: abs_lit
 * Module: my_cnf_struct
 * Parameter: lit_number
 * Return: lit_number
 * Use: abs(lit)
 */

int calculate_cn2(int t);
/*
 * Function Name: calculate_cn2
 * Module: my_cnf_struct
 * Parameter: root*
 * Return: int (if t is 1, return 0)
 * Use: calculate cn2
 */

void initialize_root(root* proot);
/*
 * Function Name: initialize_root
 * Module: my_cnf_struct
 * Parameter: root*
 * Return: void
 * Use: initialize the root
 */

void free_root(root* proot);
/*
 * Function Name: free_root
 * Module: my_cnf_struct
 * Parameter: root*
 * Return: void
 * Use: free the root
 */

#endif /* my_cnf_struct_h */
