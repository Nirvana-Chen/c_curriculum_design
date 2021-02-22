//
//  sudoku_solver.c
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/20.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#include "sudoku_solver.h"

void create_square_lit_node(node* tail, lit_number lit, int square_num) {
    node* temp_node = NULL;
    if ((temp_node = (node*)malloc(sizeof(node))) == NULL) exit(2);
    temp_node->lit = lit;
    temp_node->square_number = square_num;
    temp_node->lit_node = NULL;
    tail->lit_node = temp_node;
}

void lit_correspondence(sudoku_root* su_root) {
    int temp[10];
    lit_number lit_count = 0;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (su_root->grid[i][j].exist_status != PENDING) continue;
            for (int m = 0; m < 10; m++)
                temp[m] = PENDING;
            for (int m = 1; m <= 9; m++) {
                //row
                if (su_root->grid[i][m].exist_status != PENDING)
                    temp[su_root->grid[i][m].exist_status] = 1;
                //column
                if (su_root->grid[m][j].exist_status != PENDING)
                    temp[su_root->grid[m][j].exist_status] = 1;
            }
            //box
            int mod_i = (i-1) % 3;
            int mod_j = (j-1) % 3;
            for (int m = i - mod_i; m <= i + 2-mod_i; m++) {
                for (int n = j - mod_j; n <= j + 2-mod_j; n++) {
                    if (su_root->grid[m][n].exist_status != PENDING)
                        temp[su_root->grid[m][n].exist_status] = 1;
                }
            }
            //create square lit node
            int choice_num = 0;
            for (int m = 1; m <= 9; m++) {
                if (temp[m] != PENDING) continue;
                node* tail = su_root->grid[i][j].lit_node;
                while (tail->lit_node != NULL)
                    tail = tail->lit_node;
                lit_count++;
                choice_num++;
                create_square_lit_node(tail, lit_count, m);
            }
            su_root->grid[i][j].available_num = choice_num;
        }
    }
    su_root->lit_num = lit_count;
}

void rcb_correspondence(sudoku_root* su_root) {
    node* tail = NULL;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            //box counter
            int block = (j-1)/3 + ((i-1)/3)*3 + 1;
            int t_square = (j-1) % 3 + ((i-1) % 3) * 3 + 1;
            if (su_root->grid[i][j].exist_status == PENDING) {
                for (node* t_lit_node = su_root->grid[i][j].lit_node->lit_node; t_lit_node != NULL; t_lit_node = t_lit_node->lit_node) {
                    //row
                    su_root->row[i][t_lit_node->square_number].exist_status = PENDING;
                    su_root->row[i][t_lit_node->square_number].available_num++;
                    tail = su_root->row[i][t_lit_node->square_number].lit_node;
                    while (tail->lit_node != NULL)
                        tail = tail->lit_node;
                    create_square_lit_node(tail, t_lit_node->lit, j);
                    //column
                    su_root->column[j][t_lit_node->square_number].exist_status = PENDING;
                    su_root->column[j][t_lit_node->square_number].available_num++;
                    tail = su_root->column[j][t_lit_node->square_number].lit_node;
                    while (tail->lit_node != NULL)
                        tail = tail->lit_node;
                    create_square_lit_node(tail, t_lit_node->lit, i);
                    //box
                    su_root->box[block][t_lit_node->square_number].exist_status = PENDING;
                    su_root->box[block][t_lit_node->square_number].available_num++;
                    tail = su_root->box[block][t_lit_node->square_number].lit_node;
                    while (tail->lit_node != NULL)
                        tail = tail->lit_node;
                    create_square_lit_node(tail, t_lit_node->lit, t_square);
                }
            }
            else {
                su_root->row[i][su_root->grid[i][j].exist_status].exist_status = j;
                su_root->column[j][su_root->grid[i][j].exist_status].exist_status = i;
                su_root->box[block][su_root->grid[i][j].exist_status].exist_status = t_square;
            }
        }
    }
}

void clause_count(sudoku_root* su_root) {
    clause_number clau_count = 0;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (su_root->grid[i][j].exist_status == PENDING) {
                clau_count++;
                clau_count += calculate_cn2(su_root->grid[i][j].available_num);
            }
            if (su_root->row[i][j].exist_status == PENDING) {
                clau_count++;
                clau_count += calculate_cn2(su_root->row[i][j].available_num);
            }
            if (su_root->column[i][j].exist_status == PENDING) {
                clau_count++;
                clau_count += calculate_cn2(su_root->column[i][j].available_num);
            }
            if (su_root->box[i][j].exist_status == PENDING) {
                clau_count++;
                clau_count += calculate_cn2(su_root->box[i][j].available_num);
            }
        }
    }
    su_root->clau_num = clau_count;
}

fun_status create_cnf(sudoku_root* su_root) {
    su_root->cnf_root = (root*)malloc(sizeof(root));
    initialize_root(su_root->cnf_root);
    su_root->cnf_root->lit_num = su_root->lit_num;
    su_root->cnf_root->ini_clau_num = su_root->clau_num;
    //calloc for clauses
    if ((su_root->cnf_root->ini_clau_cnf = (clauses*)calloc(su_root->cnf_root->ini_clau_num + 1, sizeof(clauses))) == NULL) exit(2);
    su_root->cnf_root->ini_clau_cnf[0].clau_unit = NULL;
    //calloc for literals and initialization
    if ((su_root->cnf_root->literal_cnf = (literals*)calloc(su_root->cnf_root->lit_num + 1, sizeof(literals))) == NULL) exit(2);
    for (int i = 1; i <= su_root->cnf_root->lit_num; i++) {
        su_root->cnf_root->literal_cnf[i].lit_unit = NULL;
    }
    //initialization
    for (int i = 1; i <= su_root->cnf_root->ini_clau_num; i++) {
        su_root->cnf_root->ini_clau_cnf[i].active_lit_num = 0;
        su_root->cnf_root->ini_clau_cnf[i].clau_unit = NULL;
    }
    //create cnf to units
    clause_number clause_count = 0;
    int time_count;
    lit_number temp_lit = 0;
    
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (su_root->grid[i][j].exist_status == PENDING) {
                for (node* t_lit_node = su_root->grid[i][j].lit_node->lit_node; t_lit_node != NULL; t_lit_node = t_lit_node->lit_node) {
                    for (node* t_node_next = t_lit_node->lit_node; t_node_next != NULL; t_node_next = t_node_next->lit_node) {
                        clause_count++;
                        time_count = 2;
                        while (time_count) {
                            if (time_count == 2)
                                temp_lit = -t_lit_node->lit;
                            else
                                temp_lit = -t_node_next->lit;
                            create_cnf_node(su_root->cnf_root, temp_lit, clause_count);
                            time_count--;
                        }
                    }
                }
                clause_count++;
                for (node* t_lit_node = su_root->grid[i][j].lit_node->lit_node; t_lit_node != NULL; t_lit_node = t_lit_node->lit_node) {
                    temp_lit = t_lit_node->lit;
                    create_cnf_node(su_root->cnf_root, temp_lit, clause_count);
                }
            }
        }
    }
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (su_root->row[i][j].exist_status == PENDING) {
                for (node* t_lit_node = su_root->row[i][j].lit_node->lit_node; t_lit_node != NULL; t_lit_node = t_lit_node->lit_node) {
                    for (node* t_node_next = t_lit_node->lit_node; t_node_next != NULL; t_node_next = t_node_next->lit_node) {
                        clause_count++;
                        time_count = 2;
                        while (time_count) {
                            if (time_count == 2)
                                temp_lit = -t_lit_node->lit;
                            else
                                temp_lit = -t_node_next->lit;
                            create_cnf_node(su_root->cnf_root, temp_lit, clause_count);
                            time_count--;
                        }
                    }
                }
                clause_count++;
                for (node* t_lit_node = su_root->row[i][j].lit_node->lit_node; t_lit_node != NULL; t_lit_node = t_lit_node->lit_node) {
                    temp_lit = t_lit_node->lit;
                    create_cnf_node(su_root->cnf_root, temp_lit, clause_count);
                }
            }
        }
    }
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (su_root->column[i][j].exist_status == PENDING) {
                for (node* t_lit_node = su_root->column[i][j].lit_node->lit_node; t_lit_node != NULL; t_lit_node = t_lit_node->lit_node) {
                    for (node* t_node_next = t_lit_node->lit_node; t_node_next != NULL; t_node_next = t_node_next->lit_node) {
                        clause_count++;
                        time_count = 2;
                        while (time_count) {
                            if (time_count == 2)
                                temp_lit = -t_lit_node->lit;
                            else
                                temp_lit = -t_node_next->lit;
                            create_cnf_node(su_root->cnf_root, temp_lit, clause_count);
                            time_count--;
                        }
                    }
                }
                clause_count++;
                for (node* t_lit_node = su_root->column[i][j].lit_node->lit_node; t_lit_node != NULL; t_lit_node = t_lit_node->lit_node) {
                    temp_lit = t_lit_node->lit;
                    create_cnf_node(su_root->cnf_root, temp_lit, clause_count);
                }
            }
        }
    }
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (su_root->box[i][j].exist_status == PENDING) {
                for (node* t_lit_node = su_root->box[i][j].lit_node->lit_node; t_lit_node != NULL; t_lit_node = t_lit_node->lit_node) {
                    for (node* t_node_next = t_lit_node->lit_node; t_node_next != NULL; t_node_next = t_node_next->lit_node) {
                        clause_count++;
                        time_count = 2;
                        while (time_count) {
                            if (time_count == 2)
                                temp_lit = -t_lit_node->lit;
                            else
                                temp_lit = -t_node_next->lit;
                            create_cnf_node(su_root->cnf_root, temp_lit, clause_count);
                            time_count--;
                        }
                    }
                }
                clause_count++;
                for (node* t_lit_node = su_root->box[i][j].lit_node->lit_node; t_lit_node != NULL; t_lit_node = t_lit_node->lit_node) {
                    temp_lit = t_lit_node->lit;
                    create_cnf_node(su_root->cnf_root, temp_lit, clause_count);
                }
            }
        }
    }
    su_root->cnf_root->ini_clau_num = clause_count;
    return (su_root->clau_num == su_root->cnf_root->ini_clau_num ? OK : ERROR);
}

void ascertain_square(sudoku_root* su_root) {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (su_root->grid[i][j].exist_status == PENDING) {
                for (node* t_lit_node = su_root->grid[i][j].lit_node->lit_node; t_lit_node != NULL; t_lit_node = t_lit_node->lit_node) {
                    if (su_root->cnf_root->literal_cnf[t_lit_node->lit].exist_status == PLUS) {
                        su_root->grid[i][j].exist_status = t_lit_node->square_number;
                        continue;
                    }
                }
            }
        }
    }
}
