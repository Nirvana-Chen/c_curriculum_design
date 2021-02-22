//
//  main.c
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/3.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#include "main.h"

int algorithm;

int main(void) {
    int op_main = 1;
    root* proot = (root*)malloc(sizeof(root));
    initialize_root(proot);
    sudoku_root* su_root = (sudoku_root*)malloc(sizeof(sudoku_root));
    initialize_sudoku_root(su_root);
    while (op_main) {
        if (op_main > 2) {
            printf("\nWrong input!\n");
            printf("\nPress any key to continue...\n");
            getchar();
        }
        op_main = menu_main();
        switch(op_main) {
            case 1:
                sat_solver(proot);
                break;
            case 2:
                sudoku(su_root);
                break;
        }
    }
    printf("\nWelcome again!\n");
    printf("\nPress any key to quit...\n");
    getchar();
    return 0;
}

fun_status menu_main(void) {
    int op;
    system("clear");
    printf("+-----------------------------------------------------------+\n");
    printf("|    Copyright © 2019 Nirvana.Chen. All rights reserved.    |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("\n                Curriculum Design Project 1\n\n");
    printf("                          Main Menu\n");
    printf("-------------------------------------------------------------\n");
    printf("        1. SAT Solver             2. Sudoku Game\n");
    printf("                                  0. Exit\n");
    printf("-------------------------------------------------------------\n");
    printf("    Give the choice[0~2]: ");
    scanf("%d", &op);
    getchar();
    return op;
}

void sat_solver(root* proot) {
    int op = 1;
    algorithm = 2;
    while (op) {
        if (op > 6) {
            printf("\nWrong input!\n");
            printf("\nPress any key to continue...\n");
            getchar();
        }
        op = menu_sat();
        switch(op) {
            case 1:
                if (proot->cnf_file_name != NULL) {
                    printf("\nAlready have cnf in memory! Exit to main menu first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                if (load_cnf(proot))
                    printf("\nLoad successfully!\n");
                else
                    printf("\nLoad failed!\n");
                printf("\nPress any key to continue...\n");
                getchar();
                break;
            case 2:
                if (proot->cnf_file_name == NULL) {
                    printf("\nNo cnf in memory! Load first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                if (proot->total_time == 0) {
                    printf("\nNot solved yet! Solve first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                if (save_cnf(proot))
                    printf("\nSave successfully!\n");
                else
                    printf("\nSave failed!\n");
                printf("\nPress any key to continue...\n");
                getchar();
                break;
            case 3:
                if (proot->cnf_file_name == NULL) {
                    printf("\nNo cnf in memory! Load first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                print_cnf(proot);
                printf("\nPress any key to continue...\n");
                getchar();
                break;
            case 4:
                if (proot->cnf_file_name == NULL) {
                    printf("\nNo cnf in memory! Load first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                printf("\nProgressing. Please wait...\n");
                if (dpll(proot)) {
                    printf("\nsat, for more info see result in result.res\n%f ms\n", proot->total_time);
                    printf("\noutput check code: %d (1: TRUE; 0: FALSE)\n", output_check(proot));
                }
                else
                    printf("\nunsat, for more info see result in result.res\n%f ms\n", proot->total_time);
                printf("\nPress any key to continue...\n");
                getchar();
                break;
            case 5:
                if (proot->cnf_file_name == NULL) {
                    printf("\nNo cnf in memory! Load first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                printf("\nres file check code: %d (1: TRUE; 0: FALSE)\n", res_file_check(proot));
                getchar();
                break;
            case 6:
                if (proot->cnf_file_name == NULL) {
                    printf("\nNo cnf in memory! Load first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                printf("\nInput the algorithm number(1: original; 2: optimised):");
                scanf("%d", &algorithm);
                getchar();
                break;
        }
    }
    free_root(proot);
    printf("\nThe program will exit to main menu.\n");
    printf("\nPress any key to continue...\n");
    getchar();
}

fun_status menu_sat(void) {
    int op;
    system("clear");
    printf("+-----------------------------------------------------------+\n");
    printf("|    Copyright © 2019 Nirvana.Chen. All rights reserved.    |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("\n                Curriculum Design Project 1\n\n");
    printf("                     Menu for SAT Solver\n");
    printf("-------------------------------------------------------------\n");
    printf("        1. load cnf file          4. solver\n");
    printf("        2. save cnf file          5. res file check\n");
    printf("        3. print cnf              6. choose algorithm\n");
    printf("                                  0. exit to main menu\n");
    printf("-------------------------------------------------------------\n");
    printf("Now is using algorithm %d.(1: original; 2: optimised)\n\n", algorithm);
    printf("    Give the choice[0~6]: ");
    scanf("%d", &op);
    getchar();
    return op;
}

void sudoku(sudoku_root* su_root) {
    int op = 1;
    algorithm = 1;
    while (op) {
        if (op > 8) {
            printf("\nWrong input!\n");
            printf("\nPress any key to continue...\n");
            getchar();
        }
        op = menu_sudoku();
        switch(op) {
            case 1:
                if (su_root->grid[0][0].exist_status) {
                    printf("\nSudoku already in memory! Exit to main menu first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                if (load_sudoku(su_root))
                    printf("\nLoad successfully!\n");
                else
                    printf("\nLoad failed!\n");
                printf("\nPress any key to continue...\n");
                getchar();
                break;
            case 2:
                if (!su_root->grid[0][0].exist_status) {
                    printf("\nNo sudoku in memory! Load first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                if (su_root->cnf_root == NULL) {
                    su_root->cnf_root = (root*)malloc(sizeof(root));
                    initialize_root(su_root->cnf_root);
                }
                else
                    free_root(su_root->cnf_root);
                load_cnf(su_root->cnf_root);
                printf("\nPress any key to continue...\n");
                getchar();
                break;
            case 3:
                if (!su_root->grid[0][0].exist_status) {
                    printf("\nNo sudoku in memory! Load first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                if (su_root->cnf_root != NULL) {
                    free_root(su_root->cnf_root);
                    free(su_root->cnf_root);
                }
                lit_correspondence(su_root);
                rcb_correspondence(su_root);
                clause_count(su_root);
                create_cnf(su_root);
                printf("\nSudoku cnf created!\n");
                printf("\nPress any key to continue...\n");
                getchar();
                break;
            case 4:
                if (!su_root->grid[0][0].exist_status) {
                    printf("\nNo sudoku in memory! Load first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                if (su_root->cnf_root == NULL) {
                    printf("\nNo cnf in memory now! Load or create cnf first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                dpll_main(su_root->cnf_root);
                ascertain_square(su_root);
                print_sudoku(su_root);
                printf("\nThis sudoku is solved. Save the result? (yes: 1; no: 0)\nYour choice: ");
                int choice;
                scanf("%d", &choice);
                getchar();
                if (choice)
                    save_solution(su_root);
                
                op = 0;
                break;
            case 5:
                if (!su_root->grid[0][0].exist_status) {
                    printf("\nNo sudoku in memory! Load first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                print_sudoku(su_root);
                printf("\nPress any key to continue...\n");
                getchar();
                break;
            case 6:
                if (!su_root->grid[0][0].exist_status) {
                    printf("\nNo sudoku in memory! Load first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                if (su_root->cnf_root == NULL) {
                    printf("\nNo cnf in memory now! Load or create cnf first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                print_sudoku_cnf(su_root);
                printf("\nPress any key to continue...\n");
                getchar();
                break;
            case 7:
                if (!su_root->grid[0][0].exist_status) {
                    printf("\nSudoku already in memory! Exit to main menu first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                if (su_root->cnf_root == NULL) {
                    printf("\nNo cnf in memory now! Load or create cnf first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                if (save_sudoku(su_root))
                    printf("\nSave successfully!\n");
                else
                    printf("\nSave failed!\n");
                printf("\nPress any key to continue...\n");
                getchar();
                break;
            case 8:
                if (su_root->grid[0][0].exist_status) {
                    printf("\nSudoku already in memory! Exit to main menu first!\n");
                    printf("\nPress any key to continue...\n");
                    getchar();
                    break;
                }
                if (sudoku_creator(su_root))
                    printf("\nCreate successfully!\n");
                else
                    printf("\nCreate failed!\n");
                printf("\nPress any key to continue...\n");
                getchar();
                break;
        }
    }
    free_sudoku_square(su_root);
    initialize_sudoku_square(su_root);
    if (su_root->cnf_root != NULL) {
        free_root(su_root->cnf_root);
        free(su_root->cnf_root);
    }
    printf("\nThe program will exit to main menu.\n");
    printf("\nPress any key to continue...\n");
    getchar();
}

fun_status menu_sudoku(void) {
    int op;
    system("clear");
    printf("+-----------------------------------------------------------+\n");
    printf("|    Copyright © 2019 Nirvana.Chen. All rights reserved.    |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("\n                Curriculum Design Project 1\n\n");
    printf("                     Menu for Sudoku Game\n");
    printf("-------------------------------------------------------------\n");
    printf("        1. load sudoku            5. print sudoku\n");
    printf("        2. load sudoku cnf        6. print sudoku cnf\n");
    printf("        3. create sudoku cnf      7. save sudoku cnf\n");
    printf("        4. solve sudoku           8. create sudoku\n");
    printf("                                  0. exit to main menu\n");
    printf("-------------------------------------------------------------\n");
    printf("    Give the choice[0~7]: ");
    scanf("%d", &op);
    getchar();
    return op;
}
