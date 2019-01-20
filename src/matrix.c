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

#include "matrix.h"

#include <stdlib.h>
#include <string.h>

matrix *matrix_create(int size) {
    matrix *mat;

    mat = (matrix *)malloc(sizeof(matrix));
    mat->size = size + 1;
    mat->count = 0;

    mat->ia = (int *)malloc(mat->size * sizeof(int));
    memset(mat->ia, 0, mat->size * sizeof(int));

    mat->ja = (int *)malloc(mat->size * sizeof(int));
    memset(mat->ja, 0, mat->size * sizeof(int));

    mat->ar = (double *)malloc(mat->size * sizeof(double));
    memset(mat->ar, 0, mat->size * sizeof(double));

    return mat;
}

void matrix_destroy(matrix *mat) {
    if (mat) {
        free((void *)mat->ia);
        free((void *)mat->ja);
        free((void *)mat->ar);
        free((void *)mat);
    }
}

void matrix_insert(matrix *mat, int row, int col, int coef) {
    if (mat->count >= mat->size) {
        return;
    }

    mat->count++;

    mat->ia[mat->count] = row;
    mat->ja[mat->count] = col;
    mat->ar[mat->count] = coef;
}
