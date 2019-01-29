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
