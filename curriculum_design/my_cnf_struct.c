//
//  my_cnf_struct.c
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/11.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#include "my_cnf_struct.h"

char* file_name_parser(void) {
    char* str = NULL;
    int str_size = STRLEN;
    int str_length = 0;
    char input;
    str = (char*)malloc(sizeof(char) * STRLEN);
    printf("Please enter the file path: \n");
    while((input = getchar()) != '\n') {
        str[str_length++] = input;
        if(str_length == STRLEN) {
            str_size += STRLEN;
            str = (char*)realloc(str, str_size);
        }
    }
    str[str_length] = '\0';
    return str;
}

lit_number abs_lit(lit_number plit) {
    return plit > 0 ? plit : -plit;
}

int calculate_cn2(int t) {
    if (t == 1)
        return 0;
    else
        return (t * (t-1) / 2);
}

void initialize_root(root* proot) {
    proot->lit_num = 0;
    proot->ini_clau_num = 0;
    proot->stu_clau_num = 0;
    proot->ini_clau_cnf = NULL;
    proot->stu_clau_cnf = NULL;
    proot->cnf_file_name = NULL;
    proot->literal_cnf = NULL;
    proot->total_time = 0;
}

void free_root(root* proot) {
    for (clause_number i = 1; i <= proot->ini_clau_num; i++) {
        while (proot->ini_clau_cnf[i].clau_unit != NULL) {
            unit* temp = proot->ini_clau_cnf[i].clau_unit;
            proot->ini_clau_cnf[i].clau_unit = temp->clau_unit;
            free(temp);
        }
    }
    free(proot->cnf_file_name);
    free(proot->ini_clau_cnf);
    free(proot->literal_cnf);
    proot->ini_clau_cnf = NULL;
    proot->stu_clau_cnf = NULL;
    proot->cnf_file_name = NULL;
    proot->literal_cnf = NULL;
    proot->lit_num = 0;
    proot->ini_clau_num = 0;
    proot->stu_clau_num = 0;
    proot->total_time = 0;
}
