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

#ifndef COLUMN_H
#define COLUMN_H

#include "order.h"

#include <stdio.h>

double *column_create(int column_count, double value, int index);

void column_print(double *columns, int column_count, FILE *fd);

void columns_matrix_print(double **columns_matrix, int column_count, FILE *fd);

void columns_matrix_destroy(double **columns_matrix, int column_count);

double **columns_matrix_compute(order **orders, int order_count, int max_width);

#endif
