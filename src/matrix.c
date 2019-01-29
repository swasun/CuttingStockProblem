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
