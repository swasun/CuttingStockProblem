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

#include "column.h"

#include <stdlib.h>
#include <string.h>

double *column_create(int column_count, int count, int index) {
    double *column;

    column = (double *)malloc(column_count * sizeof(double));
    memset(column, 0, column_count * sizeof(double));
    column[index] = count;

    return column;
}

void column_print(double *columns, int column_count, FILE *fd) {
    int i;

    for (i = 0; i < column_count; i++) {
        fprintf(fd, "%f ", columns[i]);
    }
}

void columns_matrix_print(double **columns_matrix, int column_count, FILE *fd) {
    int i;

    for (i = 0; i < column_count; i++) {
        column_print(columns_matrix[i], column_count, fd);
        fprintf(fd, "\n");
    }
}

void columns_matrix_destroy(double **columns_matrix, int column_count) {
    int i;

    if (columns_matrix) {
        for (i = 0; i < column_count; i++) {
            free((void *)columns_matrix[i]);
        }
        free((void *)columns_matrix);
    }
}

double **columns_matrix_compute(order **orders, int order_count, int max_width) {
    double **columns_matrix;
    int i;

    columns_matrix = (double **)malloc(order_count * sizeof(double *));

    for (i = 0; i < order_count; i++) {
        if (orders[i]->width > max_width) {
            printf("[ERROR] Not correctly bound. The width must be less that that the maximal width.\n");
            columns_matrix_destroy(columns_matrix, order_count);
            return NULL;
        }

        /* For each order width, create a column with only that width */
        int count = min(orders[i]->demand, max_width / orders[i]->width);
        columns_matrix[i] = column_create(order_count, count, i);
    }

    return columns_matrix;
}
