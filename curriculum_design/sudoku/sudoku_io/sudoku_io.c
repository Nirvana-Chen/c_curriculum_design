//
//  sudoku_io.c
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/20.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#include "sudoku_io.h"

fun_status load_sudoku(sudoku_root* su_root) {
    FILE* pcnf_file = NULL;
    printf("\nload the sudoku from file:\n");
    su_root->cnf_file_name = file_name_parser();
    //file check
    if ((pcnf_file = fopen(su_root->cnf_file_name, "r")) == NULL) return INFEASTABLE;
    //read holes info
    char c;
    while (1) {
        fscanf(pcnf_file, "%c", &c);
        if (c == 'h') {
            fscanf(pcnf_file, "%c", &c);
            if (c == 'o') {
                fscanf(pcnf_file, "%c", &c);
                if (c == 'l') {
                    fscanf(pcnf_file, "%c", &c);
                    if (c == 'e') {
                        fscanf(pcnf_file, "%c", &c);
                        if (c == 's') {
                            fscanf(pcnf_file, "%c", &c);
                            if (c == ':') {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    fscanf(pcnf_file, "%d", &su_root->holes);
    //read the 9*9 grid info
    while (1) {
        fscanf(pcnf_file, "%c", &c);
        if (c == 'c') {
            fscanf(pcnf_file, "%c", &c);
            if (c == ' ') {
                break;
            }
        }
    }
    for (int i = 1; i <= 9; i++) {
        while (1) {
            fscanf(pcnf_file, "%c", &c);
            if (c == 'c') {
                fscanf(pcnf_file, "%c", &c);
                if (c == ' ') {
                    break;
                }
            }
        }
        for (int j = 1; j <= 9; j++) {
            fscanf(pcnf_file, "%c", &c);
            if (c == '.') {
                su_root->grid[i][j].exist_status = 0;
            }
            else {
                su_root->grid[i][j].exist_status = c - '1' + 1;
            }
        }
    }
    fclose(pcnf_file);
    su_root->grid[0][0].exist_status = TRUE;
    return OK;
}

fun_status save_sudoku(sudoku_root* su_root) {
    FILE* pcnf_file = NULL;
    printf("\nsave the sudoku to file:\n");
    su_root->cnf_file_name = file_name_parser();
    //file check
    if ((pcnf_file = fopen(su_root->cnf_file_name, "r")) == NULL) return INFEASTABLE;
    //output
    fprintf(pcnf_file, "c sudoku, order: 9, holes: %d\nc \n", su_root->holes);
    for (int i = 1; i <= 9; i++) {
        fprintf(pcnf_file, "c ");
        for (int j = 1; j <= 9; j++) {
            if (su_root->grid[i][j].exist_status == 0) {
                fprintf(pcnf_file, ".");
            }
            else {
                fprintf(pcnf_file, "%d", su_root->grid[i][j].exist_status);
            }
        }
        fprintf(pcnf_file, "\n");
    }
    fprintf(pcnf_file, "c \n");
    fprintf(pcnf_file, "p cnf %d %lu\n", su_root->cnf_root->lit_num, su_root->cnf_root->ini_clau_num);
    for (clause_number i = 1; i <= su_root->cnf_root->ini_clau_num; i++) {
        unit* temp_unit = su_root->cnf_root->ini_clau_cnf[i].clau_unit;
        while (temp_unit != NULL) {
            fprintf(pcnf_file, "%d ", temp_unit->literal);
            temp_unit = temp_unit->clau_unit;
        }
        fprintf(pcnf_file, "0\n");
    }
    fclose(pcnf_file);
    return OK;
}

fun_status print_sudoku(sudoku_root* su_root) {
    printf("c sudoku, order: 9, holes: %d\nc \nc \n", su_root->holes);
    printf("c     +---+---+---+---+---+---+---+---+---+\n");
    for (int i = 1; i <= 9; i++) {
        printf("c     | ");
        for (int j = 1; j <= 9; j++) {
            if (su_root->grid[i][j].exist_status == PENDING) {
                printf("  | ");
            }
            else {
                printf("%d | ", su_root->grid[i][j].exist_status);
            }
        }
        printf("\nc     +---+---+---+---+---+---+---+---+---+\n");
    }
    printf("c \nc \nc \n");
    return OK;
}

fun_status print_sudoku_cnf(sudoku_root* su_root) {
    printf("c sudoku, order: 9, holes: %d\nc \n", su_root->holes);
    for (int i = 1; i <= 9; i++) {
        printf("c ");
        for (int j = 1; j <= 9; j++) {
            if (su_root->grid[i][j].exist_status == PENDING) {
                printf(".");
            }
            else {
                printf("%d", su_root->grid[i][j].exist_status);
            }
        }
        printf("\n");
    }
    printf("c \n");
    printf("p cnf %d %lu\n", su_root->cnf_root->lit_num, su_root->cnf_root->ini_clau_num);
    for (clause_number i = 1; i <= su_root->cnf_root->ini_clau_num; i++) {
        //printf("dpll status: %d; active lit num: %d *", su_root->cnf_root->ini_clau_cnf[i].dpll_status, su_root->cnf_root->ini_clau_cnf[i].active_lit_num);
        unit* temp_unit = su_root->cnf_root->ini_clau_cnf[i].clau_unit;
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

fun_status save_solution(sudoku_root* su_root) {
    FILE* pcnf_file = NULL;
    printf("\nsave the sudoku solution to file:\n");
    char* file_path = file_name_parser();
    //file check
    if ((pcnf_file = fopen(file_path, "r")) == NULL) return INFEASTABLE;
    //output
    fprintf(pcnf_file, "c sudoku solution\nc \n");
    for (int i = 1; i <= 9; i++) {
        fprintf(pcnf_file, "c ");
        for (int j = 1; j <= 9; j++) {
            fprintf(pcnf_file, "%d", su_root->grid[i][j].exist_status);
        }
        fprintf(pcnf_file, "\n");
    }
    fprintf(pcnf_file, "c \n");
    return OK;
}

fun_status print_solution(sudoku_root* su_root) {
    printf("c sudoku solution\nc \n");
    for (int i = 1; i <= 9; i++) {
        printf("c ");
        for (int j = 1; j <= 9; j++) {
            printf("%d", su_root->grid[i][j].exist_status);
        }
        printf("\n");
    }
    printf("c \n");
    
    return OK;
}
