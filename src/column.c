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

#include "column.h"

#include <stdlib.h>
#include <string.h>

double *column_create(int column_count, double value, int index) {
    double *column;

    column = (double *)malloc(column_count * sizeof(double));
    memset(column, 0, column_count * sizeof(double));
    column[index] = value;

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

        columns_matrix[i] = column_create(order_count, max_width / orders[i]->width, i);
    }

    return columns_matrix;
}
