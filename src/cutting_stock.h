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

#ifndef CUTTING_STOCK_H
#define CUTTING_STOCK_H

#include "order.h"

#include <stdio.h>

double *cutting_stock_compute_dual(order **orders, int order_count, double **columns_matrix, int column_count);

void cutting_stock_branch_and_cut(order **orders, int order_count, double *dual_column, int dual_column_size, int max_width, double *obj_value, double *new_pattern);

double **cutting_stock_compute_best_patterns(order **orders, int order_count, int max_width, int *best_patterns_number);

double *cutting_stock_compute(double **best_patterns, int best_patterns_number, order **orders, int order_count, double *obj_value);

void cutting_stock_print_solution(double **best_patterns, int best_patterns_number, int column_size, double *pattern_demand_repartition, double obj_value, order **orders, int order_count, FILE *fd);

#endif
