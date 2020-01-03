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

#include "order.h"
#include "bool.h"
#include "column.h"
#include "cutting_stock.h"
#include "utils.h"

#include <glpk.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

int compute_problem_from_file(char *file_name) {
    int ret = 0;
    order **orders;
    int order_count, max_width, best_patterns_number;
    double **best_patterns, *pattern_demand_repartition, obj_value;
    clock_t begin_clock, end_clock;

    orders = NULL;
    pattern_demand_repartition = NULL;
    best_patterns = NULL;
    pattern_demand_repartition = NULL;

    if (!(is_file_exists(file_name))) {
        printf("[ERROR] The specified file '%s' doesn't exists.\n", file_name);
        return -1;
    }

    if (!(orders = orders_read_from_file(file_name, &order_count, &max_width))) {
        printf("[ERROR] Failed to load orders from the file '%s'.\n", file_name);
        return -1;
    }

    begin_clock = clock();

    if (!(best_patterns = cutting_stock_compute_best_patterns(orders, order_count, max_width, &best_patterns_number))) {
        printf("[ERROR] The computation of the best patterns failed.\n");
        ret = -1;
        goto err_compute_best_patterns;
    }

    if (!(pattern_demand_repartition = cutting_stock_compute(best_patterns, best_patterns_number, orders, order_count, &obj_value))) {
        printf("[ERROR] The resolution of the problem failed.\n");
        ret = -1;
        goto err_compute;
    }

    end_clock = clock();

    printf("Execution of the algorithm in %fs.\n", (double)(end_clock - begin_clock) / CLOCKS_PER_SEC);

    cutting_stock_print_solution(best_patterns, best_patterns_number, order_count, pattern_demand_repartition, obj_value, orders, order_count, stdout);

    free(pattern_demand_repartition);

err_compute:
    columns_matrix_destroy(best_patterns, best_patterns_number);
err_compute_best_patterns:
    orders_destroy(orders, order_count);
    return ret;
}

int main(int argc, char **argv) {
    int exit_code = 0;

    glp_term_out(GLP_OFF);

    if (argc != 2) {
        printf("%s <file_name>\n", argv[0]);
        return 1;
    }

    if (compute_problem_from_file(argv[1]) < 0)
        exit_code = 1;

    glp_free_env();

    return exit_code;
}
