//
//  cnf_parser.c
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/3.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#include "cnf_parser.h"

void create_cnf_node(root* proot, lit_number temp_lit, clause_number clause_count) {
    unit* temp_unit = NULL;
    if ((temp_unit = (unit*)calloc(1, sizeof(unit))) == NULL) exit(2);
    //read information
    temp_unit->dpll_status = PENDING;
    temp_unit->literal = temp_lit;
    temp_unit->clause = clause_count;
    //head insert
    temp_unit->clau_unit = proot->ini_clau_cnf[clause_count].clau_unit;
    proot->ini_clau_cnf[clause_count].clau_unit = temp_unit;
    temp_unit->lit_unit = proot->literal_cnf[abs_lit(temp_lit)].lit_unit;
    proot->literal_cnf[abs_lit(temp_lit)].lit_unit = temp_unit;
    //self++ for clau and lit
    proot->ini_clau_cnf[clause_count].active_lit_num++;
    proot->literal_cnf[abs_lit(temp_lit)].clau_count++;
}

fun_status load_cnf(root* proot) {
    FILE* pcnf_file = NULL;
    printf("\nload the cnf from file: \n");
    proot->cnf_file_name = file_name_parser();
    //file check
    if ((pcnf_file = fopen(proot->cnf_file_name, "r")) == NULL) return INFEASTABLE;
    //read until 'p cnf'
    char c;
    while (1) {
        fscanf(pcnf_file, "%c", &c);
        if (c == 112) {
            fscanf(pcnf_file, "%c", &c);
            if (c == 32) {
                fscanf(pcnf_file, "%c", &c);
                if (c == 99) {
                    fscanf(pcnf_file, "%c", &c);
                    if (c == 110) {
                        fscanf(pcnf_file, "%c", &c);
                        if (c == 102) {
                            break;
                        }
                    }
                }
            }
        }
    }
    //read lit_num and clause_num
    fscanf(pcnf_file, "%d", &proot->lit_num);
    fscanf(pcnf_file, "%lu", &proot->ini_clau_num);
    //calloc for clauses
    if ((proot->ini_clau_cnf = (clauses*)calloc(proot->ini_clau_num + 1, sizeof(clauses))) == NULL) exit(2);
    proot->ini_clau_cnf[0].clau_unit = NULL;
    //calloc for literals and initialization
    if ((proot->literal_cnf = (literals*)calloc(proot->lit_num + 1, sizeof(literals))) == NULL) exit(2);
    for (int i = 1; i <= proot->lit_num; i++) {
        proot->literal_cnf[i].lit_unit = NULL;
    }
    //read cnf to units
    for (int i = 1; i <= proot->ini_clau_num; i++) {
        proot->ini_clau_cnf[i].active_lit_num = 0;
        proot->ini_clau_cnf[i].clau_unit = NULL;
        lit_number temp_lit;
        while (1) {
            fscanf(pcnf_file, "%d", &temp_lit);
            if (temp_lit == 0) break;
            //calloc for new unit
            create_cnf_node(proot, temp_lit, i);
        }
    }
    fclose(pcnf_file);
    return OK;
}

fun_status save_cnf(root* proot) {
    FILE* pcnf_file = NULL;
    printf("\nsave the cnf to file: \n");
    proot->cnf_file_name = file_name_parser();
    //file check
    if ((pcnf_file = fopen(proot->cnf_file_name, "w")) == NULL) return INFEASTABLE;
    //output
    time_t t;
    time(&t);
    fprintf(pcnf_file, "c This is created by Nirvana.Chen on %sc\n", ctime(&t));
    fprintf(pcnf_file, "p cnf %d %lu\n", proot->lit_num, proot->ini_clau_num);
    for (clause_number i = 1; i <= proot->ini_clau_num; i++) {
        unit* temp_unit = proot->ini_clau_cnf[i].clau_unit;
        while (temp_unit != NULL) {
            fprintf(pcnf_file, "%d ", temp_unit->literal);
            temp_unit = temp_unit->clau_unit;
        }
        fprintf(pcnf_file, "0\n");
    }
    fclose(pcnf_file);
    return OK;
}

fun_status print_cnf(root* proot) {
    //output
    time_t t;
    time(&t);
    printf("c This is printed by Nirvana.Chen on %sc\n", ctime(&t));
    printf("p cnf %d %lu\n", proot->lit_num, proot->ini_clau_num);
    for (clause_number i = 1; i <= proot->ini_clau_num; i++) {
        //printf("dpll status: %d; active lit num: %d *", proot->ini_clau_cnf[i].dpll_status, proot->ini_clau_cnf[i].active_lit_num);
        unit* temp_unit = proot->ini_clau_cnf[i].clau_unit;
        while (temp_unit != NULL) {
            if (temp_unit->dpll_status) {
                temp_unit = temp_unit->clau_unit;
                continue;
            }
            printf("%d ", temp_unit->literal);
            temp_unit = temp_unit->clau_unit;
        }
        printf("0\n");
    }
    return OK;
}
