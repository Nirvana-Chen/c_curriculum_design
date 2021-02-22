//
//  sudoku_creator.c
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/20.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#include "sudoku_creator.h"

int random_row_time;

fun_status sudoku_creator(sudoku_root* su_root) {
    create_sudoku_ending(su_root);
    int level = 0;
    printf("\nInput level(1.Easy-5.Hard):");
    scanf("%d", &level);
    getchar();
    while (level >= 6 || level <= 0) {
        printf("\nWrong input!\nInput level(1.Easy-5.Hard) again:");
        scanf("%d", &level);
        getchar();
    }
    dig_hole_algorithm(su_root, level);
    su_root->grid[0][0].exist_status = TRUE;
    return OK;
}

fun_status create_sudoku_ending(sudoku_root* su_root) {
    random_row_time = 0;
    initialize_grid(su_root);
    for (int i = 1; i < 9; i++) {
        if (!create_row(su_root, i)) {
            i = 0;
            initialize_grid(su_root);
            random_row_time = 0;
        }
    }
    for (int j = 1; j <= 9; j++) {
        int status[10];
        for (int i = 1; i <= 9; i++)
            status[i] = PENDING;
        for (int i = 1; i < 9; i++) {
            status[su_root->grid[i][j].exist_status] = TRUE;
        }
        for (int i = 1; i <= 9; i++)
            if (status[i] == PENDING) {
                su_root->grid[9][j].exist_status = i;
            }
    }
    return OK;
}

fun_status dig_hole_algorithm(sudoku_root* su_root, int level) {
    if (level > 0 && level < 2)
        random_dig(su_root, level);
    else if (level == 2)
        random_dig(su_root, level);
    else if (level == 3)
        random_dig(su_root, level);
    else if (level == 4)
        random_dig(su_root, level);
    else if (level == 5)
        sequence_dig(su_root);
    return OK;
}

//create_sudoku_ending part
void initialize_grid(sudoku_root* su_root) {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            su_root->grid[i][j].exist_status = PENDING;
        }
    }
}

fun_status create_row(sudoku_root* su_root, int row) {
    while (1) {
        if (random_row_time <= 200000) {
            if (random_row(su_root, row))
                return OK;
            continue;
        }
        return ERROR;
    }
}

fun_status random_row(sudoku_root* su_root, int row) {
    random_row_time++;
    int rand_row[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int rand_num = 0;
    int temp;
    for (int t = 1; t <= 20; t++) {
        rand_num = rand() % 8 + 2;
        temp = rand_row[rand_num];
        rand_row[rand_num] = rand_row[1];
        rand_row[1] = temp;
    }
    for (int j = 1; j <= 9; j++) {
        su_root->grid[row][j].exist_status = rand_row[j];
    }
    if (row == 1)
        return OK;
    else
        return (check_conflict(su_root, row) ? ERROR : OK);
}

fun_status check_conflict(sudoku_root* su_root, int row) {
    for (int j = 1; j <= 9; j++) {
        //column check
        for (int i = 1; i < row; i++) {
            if (su_root->grid[i][j].exist_status == su_root->grid[row][j].exist_status)
                return TRUE;
        }
        //box check
        int mod_row = (row-1) % 3;
        if (mod_row == 0)
            continue;
        int mod_j = (j-1) % 3;
        for (int m = row - mod_row; m < row; m++) {
            for (int n = j - mod_j; n <= j + 2-mod_j; n++) {
                if (su_root->grid[m][n].exist_status == su_root->grid[row][j].exist_status)
                    return TRUE;
            }
        }
    }
    return FALSE;
}

//dig_hole_algorithm part
void random_dig(sudoku_root* su_root, int level) {
    int holes = 0;
    int status[82];
    for (int i = 1; i <= 81; i++)
        status[i] = PENDING;
    if (level == 1)
        holes = rand() % 8 + 24;
    else if (level == 2)
        holes = rand() % 8 + 32;
    else if (level == 3)
        holes = rand() % 8 + 40;
    else if (level == 4)
        holes = rand() % 8 + 48;
    status[0] = 81;
    int holes_done;
    for (holes_done = 0; holes_done < holes;) {
        if (!status[0]) {
            break;
        }
        int to_dig = rand() % 81 + 1;
        if (status[to_dig] == INFEASTABLE)
            continue;
        int to_dig_i = (to_dig-1) / 9 + 1;
        int to_dig_j = to_dig % 9 + 1;
        int to_dig_num = su_root->grid[to_dig_i][to_dig_j].exist_status;
        for (int t = 1; t <= 9; t++) {
            if (t == to_dig_num)
                continue;
            if (rule_conflict(su_root, t, to_dig_i, to_dig_j))
                continue;
            su_root->grid[to_dig_i][to_dig_j].exist_status = t;
            if (sudo_solvable(su_root)) {
                su_root->grid[to_dig_i][to_dig_j].exist_status = to_dig_num;
                status[to_dig] = INFEASTABLE;
                status[0]--;
                break;
            }
        }
        if (status[to_dig] != INFEASTABLE) {
            holes_done++;
            su_root->grid[to_dig_i][to_dig_j].exist_status = PENDING;
            status[to_dig] = INFEASTABLE;
            status[0]--;
        }
    }
    su_root->holes = holes_done;
}

void jump_dig(sudoku_root* su_root) {
    //int holes = rand() % 16 + 48;


}

void snake_dig(sudoku_root* su_root) {
    //int holes = rand() % 16 + 48;


}

void sequence_dig(sudoku_root* su_root) {
    //int holes = 64;
    int ignore = rand() % 9 + 1;
    int t;
    int status[10][10] = {0};
    int holes = 0;
    for (int i = 1; i <= 9; i++) {
        if (i < 5)
            while (ignore != (t = rand() % 9 + 1))
                ignore = t;
        for (int j =1; j <= 9; j++) {
            if (i < 0)
                if (j == ignore) {
                    status[i][j] = INFEASTABLE;
                    continue;
                }
            int to_dig_num = su_root->grid[i][j].exist_status;
            for (int t = 1; t <= 9; t++) {
                if (t == to_dig_num)
                    continue;
                if (rule_conflict(su_root, t, i, j))
                    continue;
                su_root->grid[i][j].exist_status = t;
                if (sudo_solvable(su_root)) {
                    su_root->grid[i][j].exist_status = to_dig_num;
                    status[i][j] = INFEASTABLE;
                    break;
                }
            }
            if (status[i][j] != INFEASTABLE) {
                holes++;
                su_root->grid[i][j].exist_status = PENDING;
                status[i][j] = INFEASTABLE;
            }
        }
    }
    su_root->holes = holes;
}

fun_status rule_conflict(sudoku_root* su_root, int t, int i, int j) {
    for (int k = 1; k <= 9; k++) {
        for (int m = 1; m <= 9; m++) {
            //row
            if (su_root->grid[i][m].exist_status == t && m != j)
                return TRUE;
            //column
            if (su_root->grid[m][j].exist_status == t && m != i)
                return TRUE;
        }
        //box
        int mod_i = (i-1) % 3;
        int mod_j = (j-1) % 3;
        for (int m = i - mod_i; m <= i + 2-mod_i; m++) {
            for (int n = j - mod_j; n <= j + 2-mod_j; n++) {
                if (su_root->grid[m][n].exist_status == t && m != i && n != j)
                    return TRUE;
            }
        }
    }
    return FALSE;
}

fun_status sudo_solvable(sudoku_root* su_root) {
    lit_correspondence(su_root);
    rcb_correspondence(su_root);
    clause_count(su_root);
    create_cnf(su_root);
    fun_status t = dpll_main(su_root->cnf_root);
    free_sudoku_square(su_root);
    initialize_sudoku_square(su_root);
    free_root(su_root->cnf_root);
    free(su_root->cnf_root);
    su_root->cnf_root = NULL;
    return t;
}
