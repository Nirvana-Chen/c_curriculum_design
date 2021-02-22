//
//  my_sudoku_struct.c
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/21.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#include "my_sudoku_struct.h"

void initialize_sudoku_root(sudoku_root* su_root) {
    su_root->holes = 0;
    su_root->lit_num = 0;
    su_root->clau_num = 0;
    su_root->cnf_root = NULL;
    su_root->cnf_file_name = NULL;
    initialize_sudoku_square(su_root);
}

void initialize_sudoku_square(sudoku_root* su_root) {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            su_root->grid[i][j].available_num = 0;
            su_root->grid[i][j].lit_node = (node*)malloc(sizeof(node));
            su_root->grid[i][j].lit_node->lit = 0;
            su_root->grid[i][j].lit_node->lit_node = NULL;
            su_root->row[i][j].available_num = 0;
            su_root->row[i][j].lit_node = (node*)malloc(sizeof(node));
            su_root->row[i][j].lit_node->lit = 0;
            su_root->row[i][j].lit_node->lit_node = NULL;
            su_root->column[i][j].available_num = 0;
            su_root->column[i][j].lit_node = (node*)malloc(sizeof(node));
            su_root->column[i][j].lit_node->lit = 0;
            su_root->column[i][j].lit_node->lit_node = NULL;
            su_root->box[i][j].available_num = 0;
            su_root->box[i][j].lit_node = (node*)malloc(sizeof(node));
            su_root->box[i][j].lit_node->lit = 0;
            su_root->box[i][j].lit_node->lit_node = NULL;
        }
    }
    su_root->grid[0][0].exist_status = FALSE;
}

void free_sudoku_square(sudoku_root* su_root) {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            while (su_root->grid[i][j].lit_node->lit_node != NULL) {
                node* temp = su_root->grid[i][j].lit_node->lit_node;
                su_root->grid[i][j].lit_node->lit_node = temp->lit_node;
                free(temp);
            }
            while (su_root->row[i][j].lit_node->lit_node != NULL) {
                node* temp = su_root->row[i][j].lit_node->lit_node;
                su_root->row[i][j].lit_node->lit_node = temp->lit_node;
                free(temp);
            }
            while (su_root->column[i][j].lit_node->lit_node != NULL) {
                node* temp = su_root->column[i][j].lit_node->lit_node;
                su_root->column[i][j].lit_node->lit_node = temp->lit_node;
                free(temp);
            }
            while (su_root->box[i][j].lit_node->lit_node != NULL) {
                node* temp = su_root->box[i][j].lit_node->lit_node;
                su_root->box[i][j].lit_node->lit_node = temp->lit_node;
                free(temp);
            }
        }
    }
}
