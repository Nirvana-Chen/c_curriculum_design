//
//  solver.c
//  curriculum_design
//
//  Created by 陈益欣 on 2019/2/3.
//  Copyright © 2019 Nirvana.Chen. All rights reserved.
//

#include "solver.h"

clause_number step;

fun_status dpll(root* proot) {
    //set a variable for return
    fun_status sat_status = TRUE;
    //time count
    clock_t time_begin, time_over;
    time_begin = clock();
    sat_status = dpll_main(proot);
    //time count
    time_over = clock();
    proot->total_time = difftime(time_over, time_begin) / CLOCKS_PER_SEC * 1000;
    //output to file
    printf("\noutput the res file:\n");
    output_to_file(proot, sat_status);
    return sat_status;
}

fun_status dpll_main(root* proot) {
    //set a variable for return
    fun_status sat_status = TRUE;
    //dpll algorithm
    //set the return mark
    fun_status Re = 2;
    //begin
    step = 0;
    while (Re <= 4) {
        lit_number plit = 0;
        if (Re > 4) break;
        else {
#ifdef DEBUG_DPLL
            //            printf("%ld", proot->literal_cnf[abs_lit(plit)].visit_order);
            printf("before bcp\n");
            print_cnf(proot);
#endif
            //choose a free lit to assign a value, if no free lit, sat
            if (!(plit = decide(proot))) {
                Re += 8;
                break;
            }
            //mark the step
            step++;
            proot->literal_cnf[abs_lit(plit)].visit_order = step;

            //bcp deduce progress -- simplify the clauses
            while (!bcp_deduce(proot, plit)) {
#ifdef DEBUG_DPLL
                printf("bcp bug\n");
                print_cnf(proot);
#endif
                //conflict exists
                //conflict_analysis(proot);
                
                //back track to find the nearest free(not reversed) conflicting lits
                plit = back_track(proot, plit);
                //none is free, unsat
                if (!plit) {
                    Re += 6;
                    break;
                }
                else {
                    if (algorithm == 1) {
                        //reverse the lit and mark it
                        proot->literal_cnf[plit].visit_status = BCPSEC;
                        //reset the clauses to plit step
                        reset_bcp(proot, plit);
                    }
                    else if (algorithm == 2) {
#ifdef NEW_ONE
                        //reverse the lit and mark it
                        proot->literal_cnf[plit].visit_status = BCPSEC;
                        //reset the clauses to plit step
                        reset_bcp(proot, plit);
#endif
#ifdef NEW_TWO
                        //reverse the lit and mark it
                        int mark = -(proot->literal_cnf[plit].exist_status > 0 ? PLUS : MINUS);
                        proot->literal_cnf[plit].visit_status = BCPSEC;
                        //reset the clauses to plit step
                        reset_bcp(proot, plit);
                        plit = mark * plit;
#endif
                    }
#ifdef DEBUG_DPLL
                    printf("after reset\n");
                    print_cnf(proot);
#endif
                }
            }
        }
    }
    //Re == 8 means += 6, unsat
    if (Re == 8)
        sat_status = FALSE;
    //over
    return sat_status;
}

fun_status is_unit_clause(clauses* pclause) {
    if (pclause->active_lit_num == 1)
        return TRUE;
    else
        return FALSE;
}

clause_number have_unit_clause(root* proot) {
    for (clause_number i = 1; i <= proot->ini_clau_num; i++) {
        if (proot->ini_clau_cnf[i].active_lit_num == 1)
            return i;
    }
    return FALSE;
}

lit_number decide(root* proot) {
    clause_number pclause = 0;
    if (algorithm == 1) {
        if ((pclause = have_unit_clause(proot)) != 0) {
            for (unit* t_clau_unit = proot->ini_clau_cnf[pclause].clau_unit; t_clau_unit != NULL; t_clau_unit = t_clau_unit->clau_unit){
                //if is the unit lit, mark the literal UCR
                if (t_clau_unit->dpll_status == PENDING) {
                    proot->literal_cnf[abs_lit(t_clau_unit->literal)].visit_status = UCR;
                    return t_clau_unit->literal;
                }
            }
        }
        else
            for (lit_number i = 1; i <= proot->lit_num; i++) {
                if (proot->literal_cnf[i].exist_status == PENDING) {
                    return i;
                }
            }
        return FALSE;
    }
    else if (algorithm == 2) {
        lit_number plit = 0;
        if ((pclause = have_unit_clause(proot)) != 0) {
            for (unit* t_clau_unit = proot->ini_clau_cnf[pclause].clau_unit; t_clau_unit != NULL; t_clau_unit = t_clau_unit->clau_unit){
                //if is the unit lit, mark the literal UCR
                if (t_clau_unit->dpll_status == PENDING) {
                    proot->literal_cnf[abs_lit(t_clau_unit->literal)].visit_status = UCR;
                    return t_clau_unit->literal;
                }
            }
        }
        else
#ifdef NEW_ONE
            pclause = 0;
        for (lit_number i = 1; i <= proot->lit_num; i++) {
            if (proot->literal_cnf[i].exist_status == PENDING && proot->literal_cnf[i].clau_count > pclause) {
                pclause = proot->literal_cnf[i].clau_count;
                plit = i;
            }
        }
        return plit;
#endif
#ifdef NEW_TWO
        {
            plit = 20 * proot->lit_num;
            for (clause_number i = 1; i <= proot->ini_clau_num; i++) {
                if (proot->ini_clau_cnf[i].dpll_status == PENDING && proot->ini_clau_cnf[i].active_lit_num < plit) {
                    plit = proot->ini_clau_cnf[i].active_lit_num;
                    pclause = i;
                }
            }
            if (pclause == 0)
                return FALSE;
            clause_number pclause_num = 0;
            for (unit* t_clau_unit = proot->ini_clau_cnf[pclause].clau_unit; t_clau_unit != NULL; t_clau_unit = t_clau_unit->clau_unit) {
                if (t_clau_unit->dpll_status == PENDING && proot->literal_cnf[abs_lit(t_clau_unit->literal)].clau_count > pclause_num) {
                    pclause_num = proot->literal_cnf[abs_lit(t_clau_unit->literal)].clau_count;
                    plit = t_clau_unit->literal;
                }
            }
            return plit;
        }
#endif
    }
    return FALSE;
}

fun_status bcp(root* proot, lit_number plit) {
    proot->literal_cnf[abs_lit(plit)].exist_status = (plit > 0 ? PLUS : MINUS);
    if (plit < 0) {
        for (unit* temp_unit = proot->literal_cnf[-plit].lit_unit; temp_unit != NULL; temp_unit = temp_unit->lit_unit) {
            if (proot->ini_clau_cnf[temp_unit->clause].dpll_status == TRUE) continue;
            temp_unit->dpll_status = TRUE;
            proot->ini_clau_cnf[temp_unit->clause].active_lit_num--;
            proot->literal_cnf[-plit].clau_count--;
            if (temp_unit->literal < 0) {
                proot->ini_clau_cnf[temp_unit->clause].dpll_status = TRUE;
                proot->ini_clau_cnf[temp_unit->clause].visit_order = step;
                for (unit* t_clau_unit = proot->ini_clau_cnf[temp_unit->clause].clau_unit; t_clau_unit != NULL; t_clau_unit = t_clau_unit->clau_unit) {
                    if (t_clau_unit->dpll_status != TRUE) {
                        t_clau_unit->dpll_status = TRUE;
                        proot->ini_clau_cnf[t_clau_unit->clause].active_lit_num--;
                        proot->literal_cnf[abs_lit(t_clau_unit->literal)].clau_count--;
                    }
                }
            }
            else if (proot->ini_clau_cnf[temp_unit->clause].active_lit_num == 0) {
                proot->ini_clau_cnf[temp_unit->clause].dpll_status = INFEASTABLE;
                proot->ini_clau_cnf[temp_unit->clause].visit_order = step;
                return ERROR;
            }
        }
    }
    else {
        for (unit* temp_unit = proot->literal_cnf[plit].lit_unit; temp_unit != NULL; temp_unit = temp_unit->lit_unit) {
            if (proot->ini_clau_cnf[temp_unit->clause].dpll_status == TRUE) continue;
            temp_unit->dpll_status = TRUE;
            proot->ini_clau_cnf[temp_unit->clause].active_lit_num--;
            proot->literal_cnf[plit].clau_count--;
            if (temp_unit->literal > 0) {
                proot->ini_clau_cnf[temp_unit->clause].dpll_status = TRUE;
                proot->ini_clau_cnf[temp_unit->clause].visit_order = step;
                for (unit* t_clau_unit = proot->ini_clau_cnf[temp_unit->clause].clau_unit; t_clau_unit != NULL; t_clau_unit = t_clau_unit->clau_unit) {
                    if (t_clau_unit->dpll_status != TRUE) {
                        t_clau_unit->dpll_status = TRUE;
                        proot->ini_clau_cnf[t_clau_unit->clause].active_lit_num--;
                        proot->literal_cnf[abs_lit(t_clau_unit->literal)].clau_count--;
                    }
                }
            }
            else if (proot->ini_clau_cnf[temp_unit->clause].active_lit_num == 0) {
                proot->ini_clau_cnf[temp_unit->clause].dpll_status = INFEASTABLE;
                proot->ini_clau_cnf[temp_unit->clause].visit_order = step;
                return ERROR;
            }
        }
    }
    return OK;
}

fun_status bcp_deduce(root* proot, lit_number plit) {

    if (algorithm == 1) {
        switch (proot->literal_cnf[abs_lit(plit)].visit_status) {
            case UCR:
                return bcp(proot, plit);
            case PENDING:
                proot->literal_cnf[abs_lit(plit)].visit_status = BCPFIR;
                return bcp(proot, -plit);
            case BCPSEC:
                return bcp(proot, plit);
            default:
                break;
        }
        return OK;
    }
    else if (algorithm == 2) {
#ifdef NEW_ONE
        switch (proot->literal_cnf[abs_lit(plit)].visit_status) {
            case UCR:
                return bcp(proot, plit);
            case PENDING:
                proot->literal_cnf[abs_lit(plit)].visit_status = BCPFIR;
                return bcp(proot, -plit);
            case BCPSEC:
                return bcp(proot, plit);
            default:
                break;
        }
        return OK;
#endif
#ifdef NEW_TWO
        switch (proot->literal_cnf[abs_lit(plit)].visit_status) {
            case UCR:
                return bcp(proot, plit);
            case PENDING:
                proot->literal_cnf[abs_lit(plit)].visit_status = BCPFIR;
                return bcp(proot, plit);
            case BCPSEC:
                return bcp(proot, plit);
            default:
                break;
        }
        return OK;
#endif
    }
    return OK;
}

void conflict_analysis(root* proot) {
    
    
    
}

lit_number back_track(root* proot, lit_number plit) {

    if (algorithm == 1) {
        lit_number temp_lit = 0;
        clause_number temp_order = 0;
        for (lit_number i = 1; i <= proot->lit_num; i++) {
            if (proot->literal_cnf[i].visit_status == BCPFIR && proot->literal_cnf[i].visit_order > temp_order) {
                temp_order = proot->literal_cnf[i].visit_order;
                temp_lit = i;
            }
        }
        //reset step to i
        step = proot->literal_cnf[temp_lit].visit_order;
        return temp_lit;
    }
    else if (algorithm == 2) {
        lit_number temp_lit = 0;
        clause_number temp_order = 0;
        for (lit_number i = 1; i <= proot->lit_num; i++) {
            if (proot->literal_cnf[i].visit_status == BCPFIR && proot->literal_cnf[i].visit_order > temp_order) {
                temp_order = proot->literal_cnf[i].visit_order;
                temp_lit = i;
            }
        }
        //reset step to i
        step = proot->literal_cnf[temp_lit].visit_order;
        return temp_lit;
    }
    return plit;
}

void reset_bcp(root* proot, lit_number plit) {
    for (clause_number i = 1; i <= proot->ini_clau_num; i++) {
        if (proot->ini_clau_cnf[i].visit_order >= step) {
            if (proot->ini_clau_cnf[i].dpll_status == TRUE) {
                for (unit* t_clau_unit = proot->ini_clau_cnf[i].clau_unit; t_clau_unit != NULL; t_clau_unit = t_clau_unit->clau_unit){
                    if (proot->literal_cnf[abs_lit(t_clau_unit->literal)].visit_status != PENDING && proot->literal_cnf[abs_lit(t_clau_unit->literal)].visit_order < step) continue;
                    t_clau_unit->dpll_status = PENDING;
                    proot->literal_cnf[abs_lit(t_clau_unit->literal)].clau_count++;
                    proot->ini_clau_cnf[t_clau_unit->clause].active_lit_num++;
                }
            }
            proot->ini_clau_cnf[i].dpll_status = PENDING;
        }
    }
    for (lit_number i = 1; i <= proot->lit_num; i++) {
        if (proot->literal_cnf[i].visit_order >= step) {
            proot->literal_cnf[i].exist_status = PENDING;
            if (proot->literal_cnf[i].visit_order > step)
                proot->literal_cnf[i].visit_status = PENDING;
            for (unit* temp_unit = proot->literal_cnf[i].lit_unit; temp_unit != NULL; temp_unit = temp_unit->lit_unit) {
                if (proot->ini_clau_cnf[temp_unit->clause].dpll_status == TRUE) continue;
                if (temp_unit->dpll_status == PENDING) continue;
                temp_unit->dpll_status = PENDING;
                proot->literal_cnf[i].clau_count++;
                proot->ini_clau_cnf[temp_unit->clause].active_lit_num++;
            }
        }
    }
}

void output_to_file(root* proot, fun_status sat_status) {
    char* file_path = file_name_parser();
    FILE* p_res_file = NULL;
    if ((p_res_file = fopen(file_path, "w")) == NULL) return;
    fprintf(p_res_file, "s %d\n", sat_status);
    if (sat_status) {
        fprintf(p_res_file, "v ");
        for (lit_number i = 1; i <= proot->lit_num; i++) {
            if (proot->literal_cnf[i].exist_status == PENDING)
                proot->literal_cnf[i].exist_status = PLUS;
            fprintf(p_res_file, "%d ", proot->literal_cnf[i].exist_status * i);
        }
        fprintf(p_res_file, "\n");
    }
    fprintf(p_res_file, "t %f\n", proot->total_time);
    fclose(p_res_file);
}

fun_status res_file_check(root* proot) {
    char* file_path = file_name_parser();
    FILE* p_res_file = NULL;
    if ((p_res_file = fopen(file_path, "r")) == NULL) return INFEASTABLE;
    char c;
    while (1) {
        fscanf(p_res_file, "%c", &c);
        if (c == 'v') break;
    }
    int temp = 0;
    for (lit_number i = 1; i <= proot->lit_num; i++) {
        fscanf(p_res_file, "%d", &temp);
        proot->literal_cnf[i].exist_status = (temp > 0 ? PLUS : MINUS);
    }
    for (clause_number i = 1; i <= proot->ini_clau_num; i++) {
        for (unit* t_clau_unit = proot->ini_clau_cnf[i].clau_unit; t_clau_unit != NULL; t_clau_unit = t_clau_unit->clau_unit) {
            if (t_clau_unit->literal > 0) {
                if (proot->literal_cnf[abs_lit(t_clau_unit->literal)].exist_status == PLUS) break;
            }
            else {
                if (proot->literal_cnf[abs_lit(t_clau_unit->literal)].exist_status == MINUS) break;
            }
            if (t_clau_unit->clau_unit == NULL) return FALSE;
        }
    }
    return TRUE;
}

fun_status output_check(root* proot) {
    for (clause_number i = 1; i <= proot->ini_clau_num; i++) {
        for (unit* t_clau_unit = proot->ini_clau_cnf[i].clau_unit; t_clau_unit != NULL; t_clau_unit = t_clau_unit->clau_unit) {
            if (t_clau_unit->literal > 0) {
                if (proot->literal_cnf[abs_lit(t_clau_unit->literal)].exist_status == PLUS) break;
            }
            else {
                if (proot->literal_cnf[abs_lit(t_clau_unit->literal)].exist_status == MINUS) break;
            }
            if (t_clau_unit->clau_unit == NULL) return FALSE;
        }
    }
    return TRUE;
}
