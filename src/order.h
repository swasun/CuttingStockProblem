/*******************************************************************************
 * Copyright (C) 2019 Charly Lamothe, Doulkifouli Abdallah-Ali                 *
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

#ifndef ORDER_H
#define ORDER_H

#include <stdio.h>

typedef struct {
    int demand; /* Quantity of the order */
    int width; /* Width of the item */
} order;

/* Create a new order */
order *order_create(double width, int demand);

/* Deallocate the order */
void order_destroy(order *o);

void order_print(order *o, FILE *fd);

/* Read a list of commands from a file */
order **orders_read_from_file(char *file_name, int *order_count, int *max_width);

/* Deallocate a list of commands */
void orders_destroy(order **orders, int order_count);

void orders_print(order **orders, int order_count, FILE *fd);

void order_swap(order *o1, order *o2);

void orders_quicksort_by_desc_width(order **orders, int order_count);

#endif
