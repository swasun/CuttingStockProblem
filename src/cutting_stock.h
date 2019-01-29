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
