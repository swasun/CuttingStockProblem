/*************************************************************************************
 * MIT License                                                                       *
 *                                                                                   *
 * Copyright (C) 2017 Charly Lamothe, Doulkifouli Abdallah-Ali                       *
 *                                                                                   *
 * This file is part of CuttingStockProblem.                                         *
 *                                                                                   *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy    *
 *   of this software and associated documentation files (the "Software"), to deal   *
 *   in the Software without restriction, including without limitation the rights    *
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       *
 *   copies of the Software, and to permit persons to whom the Software is           *
 *   furnished to do so, subject to the following conditions:                        *
 *                                                                                   *
 *   The above copyright notice and this permission notice shall be included in all  *
 *   copies or substantial portions of the Software.                                 *
 *                                                                                   *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
 *   SOFTWARE.                                                                       *
 *************************************************************************************/

#include "cutting_stock.h"
#include "matrix.h"
#include "bool.h"
#include "utils.h"
#include "column.h"

#include <glpk.h>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

double *cutting_stock_compute_dual(order **orders, int order_count, double **columns_matrix, int column_count) {
    glp_prob *lp;
    int i, j, row, col;
    double *dual_column;
    matrix *mat;

    lp = glp_create_prob();

    glp_set_prob_name(lp, "dual_column_problem");
    glp_set_obj_dir(lp, GLP_MIN);
    glp_add_rows(lp, order_count);
    glp_add_cols(lp, column_count);

    for (i = 0, row = 1; i < order_count; i++, row++) {
        glp_set_row_bnds(lp, row, GLP_FX, orders[i]->demand, orders[i]->demand);
    }

    for (col = 1; col <= column_count; col++) {
        glp_set_col_bnds(lp, col, GLP_LO, 0.0, 0.0);
        glp_set_obj_coef(lp, col, 1.0);
    }

    mat = matrix_create(order_count * column_count);

    for (i = 0, col = 1; i < column_count; i++, col++) {
        for (j = 0, row = 1; j < order_count; j++, row++) {
            matrix_insert(mat, row, col, columns_matrix[i][j]);
        }
    }

    glp_load_matrix(lp, mat->count, mat->ia,  mat->ja,  mat->ar);

    assert(glp_simplex(lp, NULL) == 0);

    dual_column = (double *)malloc(column_count * sizeof(double));
    for (i = 0, row = 1; row <= order_count; row++, i++) {
        dual_column[i] = glp_get_row_dual(lp, row);
    }

    matrix_destroy(mat);
    glp_delete_prob(lp);

    return dual_column;
}

void cutting_stock_branch_and_cut(order **orders, int order_count, double *dual_column, int dual_column_size, int max_width, double *obj_value, double *new_pattern) {
    glp_prob *lp;
    int i, row_number, row, col_number, col;
    matrix *mat;

    lp = glp_create_prob();
    row_number = 1;
    row = 1;
    col_number = dual_column_size;

    glp_set_prob_name(lp, "branch_and_cut_problem");
    glp_set_obj_dir(lp, GLP_MAX);
    glp_add_rows(lp, order_count);
    glp_add_rows(lp, row_number);
    glp_set_row_bnds(lp, row, GLP_UP, 0.0, max_width);
    glp_add_cols(lp, col_number);

    for (i = 0, col = 1; col <= col_number; col++, i++) {
        glp_set_col_bnds(lp, col, GLP_DB, 0.0, orders[i]->demand);
        glp_set_col_kind(lp, col, GLP_IV );
        glp_set_obj_coef(lp, col, dual_column[i]);
    }

    mat = matrix_create(col_number);

    for (i = 0, col = 1; i < order_count; i++, col++) {
        matrix_insert(mat, row, col, orders[i]->width);
    }

    glp_load_matrix(lp, mat->count, mat->ia,  mat->ja,  mat->ar);

    glp_iocp param;
    glp_init_iocp(&param);
    param.presolve = GLP_ON;

    assert(glp_intopt(lp, &param) == 0);

    *obj_value = glp_mip_obj_val(lp);

    for (i = 0, col = 1; col <= col_number; col++, i++) {
        new_pattern[i] = glp_mip_col_val(lp, col);
    }

    matrix_destroy(mat);
    glp_delete_prob(lp);
}

double **cutting_stock_compute_best_patterns(order **orders, int order_count, int max_width, int *best_patterns_number) {
    double **columns_matrix, obj_value, *new_pattern, *dual_column, **best_patterns;
    int i, column_size, columns_matrix_number, temp_best_patterns_number;

    columns_matrix = columns_matrix_compute(orders, order_count, max_width);
    column_size = order_count;
    columns_matrix_number = order_count;
    best_patterns = NULL;
    temp_best_patterns_number = 0;

    while (true) {
        dual_column = cutting_stock_compute_dual(orders, order_count, columns_matrix, columns_matrix_number);

        new_pattern = (double *)malloc(column_size * sizeof(double));
        cutting_stock_branch_and_cut(orders, order_count, dual_column, column_size, max_width, &obj_value, new_pattern);

        /* Add the new pattern */
        if (columns_matrix) {
            columns_matrix = (double **)realloc(columns_matrix, (columns_matrix_number + 1) * sizeof(double *));
        } else {
            columns_matrix = (double **)malloc(sizeof(double *));
        }
        columns_matrix[columns_matrix_number] = new_pattern;
        columns_matrix_number++;

        free((void *)dual_column);

        if (obj_value <= 1.00000000001)
            break;
    }

    if (columns_matrix_number == 0) {
        columns_matrix_destroy(columns_matrix, columns_matrix_number);
        return NULL;
    }

    for (i = 0; i < columns_matrix_number; i++) {
        if (best_patterns) {
            if (!double_matrix_contains_array(best_patterns, temp_best_patterns_number, columns_matrix[i], column_size)) {
                best_patterns = (double **)realloc(best_patterns, (temp_best_patterns_number + 1) * sizeof(double *));
                best_patterns[temp_best_patterns_number] = columns_matrix[i];
                temp_best_patterns_number++;
            }
        } else {
            best_patterns = (double **)malloc(sizeof(double *));
            best_patterns[0] = columns_matrix[i];
            temp_best_patterns_number++;
        }
    }

    *best_patterns_number = temp_best_patterns_number;

    free((void *)columns_matrix);

    return best_patterns;
}

double *cutting_stock_compute(double **best_patterns, int best_patterns_number, order **orders, int order_count, double *obj_value) {
    glp_prob *lp;
    int i, j, row, col;
    matrix *mat;
    double *pattern_demand_repartition;

    lp = glp_create_prob();
    mat = NULL;
    pattern_demand_repartition = NULL;

    glp_set_obj_dir(lp, GLP_MIN);
    glp_add_rows(lp, order_count);
    glp_add_cols(lp, best_patterns_number);

    for (i = 0, row = 1; i < order_count; i++, row++) {
        glp_set_row_bnds(lp, row, GLP_FX, orders[i]->demand, orders[i]->demand);
    }

    for (col = 1; col <= best_patterns_number; col++) {
        glp_set_col_bnds(lp, col, GLP_LO, 0.0, 0.0);
        glp_set_col_kind(lp, col, GLP_IV);
        glp_set_obj_coef(lp, col, 1.0);
    }

    mat = matrix_create(best_patterns_number * order_count);
    for (i = 0, col = 1; i < best_patterns_number; i++, col++) {
        for (j = 0, row = 1; j < order_count; j++, row++) {
            matrix_insert(mat, row, col, best_patterns[i][j]);
        }
    }

    glp_load_matrix(lp, mat->count, mat->ia,  mat->ja,  mat->ar);

    assert(glp_simplex(lp, NULL) == 0);
    assert(glp_intopt(lp, NULL) == 0);

    *obj_value = glp_mip_obj_val(lp);

    pattern_demand_repartition = (double *)malloc(best_patterns_number * sizeof(double));
    for (i = 0, col = 1; col <= best_patterns_number; col++, i++) {
        pattern_demand_repartition[i] = glp_mip_col_val(lp, col);
    }

    glp_delete_prob(lp);
    matrix_destroy(mat);

    return pattern_demand_repartition;
}

void cutting_stock_print_solution(double **best_patterns, int best_patterns_number, int column_size, double *pattern_demand_repartition, double obj_value, order **orders, int order_count, FILE *fd) {
    int i, j;

    for (i = 0; i < best_patterns_number; i++) {
        if (pattern_demand_repartition[i] == 0.0) {
            continue;
        }
        fprintf(fd, "Pattern {");
        for (j = 0; j < column_size - 1; j++) {
            if (best_patterns[i][j] != 0.0) {
                fprintf(fd, " %dx%d ", (int)best_patterns[i][j], orders[j]->width);
            }
        }
        if (best_patterns[i] && best_patterns[i][j] != 0.0) {
            fprintf(fd, "%dx%d} x %f\n", (int)best_patterns[i][j], orders[j]->width, pattern_demand_repartition[i]);
        } else {
            fprintf(fd, "} x %f\n", pattern_demand_repartition[i]);
        }
    }
    fprintf(fd, "Objective value : %f\n", obj_value);
}
