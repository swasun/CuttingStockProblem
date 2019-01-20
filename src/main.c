/*******************************************************************************
 * Copyright (C) 2019 Charly Lamothe                                           *
 *                                                                             *
 * This file is part of CuttingStockProblem.                                   *
 *                                                                             *
 *   Licensed under the Apache License, Version 2.0 (the "License");           *
 *   you may not use this file except in compliance with the License.          *
 *   You may obtain a copy of the License at                                   *
 *                                                                             *
 *   http://www.apache.org/licenses/LICENSE-2.0                                *
 *                                                                             *
 *   Unless required by applicable law or agreed to in writing, software       *
 *   distributed under the License is distributed on an "AS IS" BASIS,         *
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *   See the License for the specific language governing permissions and       *
 *   limitations under the License.                                            *
 *******************************************************************************/

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

void compute_problem_from_file(char *file_name) {
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
        goto clean_up;
    }

    if (!(orders = orders_read_from_file(file_name, &order_count, &max_width))) {
        printf("[ERROR] Failed to load orders from the file '%s'.\n", file_name);
        goto clean_up;
    }

    begin_clock = clock();

    if (!(best_patterns = cutting_stock_compute_best_patterns(orders, order_count, max_width, &best_patterns_number))) {
        printf("[ERROR] The computation of the best patterns failed.\n");
        goto clean_up;
    }

    if (!(pattern_demand_repartition = cutting_stock_compute(best_patterns, best_patterns_number, orders, order_count, &obj_value))) {
        printf("[ERROR] The resolution of the problem failed.\n");
        goto clean_up;
    }

    end_clock = clock();

    printf("Execution of the algorithm in %fs.\n", (double)(end_clock - begin_clock) / CLOCKS_PER_SEC);

    cutting_stock_print_solution(best_patterns, best_patterns_number, order_count, pattern_demand_repartition, obj_value, orders, order_count, stdout);

clean_up:
    free((void *)pattern_demand_repartition);
    columns_matrix_destroy(best_patterns, best_patterns_number);
    orders_destroy(orders, order_count);
}

int main(int argc, char **argv) {
    glp_term_out(GLP_OFF);

    if (argc != 2) {
        printf("%s <file_name>\n", argv[0]);
        return 0;
    }

    compute_problem_from_file(argv[1]);

    glp_free_env();

    return 0;
}
