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
#include "utils.h"

#include <stdlib.h>
#include <errno.h>

order *order_create(double width, int demand) {
    order *o;

    o = (order *)malloc(sizeof(order));
    o->width = width;
    o->demand = demand;

    return o;
}

void order_destroy(order *o) {
    if (o) {
        free((void *)o);
        o = NULL;
    }
}

void order_print(order *o, FILE *fd) {
    fprintf(fd, "width:%d, demand:%d\n", o->width, o->demand);
}

order **orders_read_from_file(char *file_name, int *order_count, int *max_width) {
    FILE *input_file;
    char line[MAX_LINE];
    int i, width, demand;
    order **orders;

    input_file = NULL;
    *order_count = 0;
    *max_width = 0;
    i = 0;
    width = 0;
    demand = 0;
    orders = NULL;

    if (!(input_file = fopen(file_name, "r"))) {
        perror("input_file");
        return NULL;
    }

    *order_count = get_lines_number(input_file) - 1;

    fgets(line, MAX_LINE, input_file);
    sscanf(line, "%d\n", max_width);

    orders = (order **)malloc(*order_count * sizeof(order *));

    while (fgets(line, MAX_LINE, input_file)) {
        sscanf(line, "%d %d\n", &width, &demand);
        orders[i] = order_create(width, demand);
        i++;
    }

    fclose(input_file);

    return orders;
}

void orders_destroy(order **orders, int order_count) {
    int i;

    if (orders) {
        for (i = 0; i < order_count; i++) {
            order_destroy(orders[i]);
        }
        free((void *)orders);
        orders = NULL;
    }
}

void orders_print(order **orders, int order_count, FILE *fd) {
    int i;

    for (i = 0; i < order_count; i++) {
        order_print(orders[i], fd);
    }
}

void order_swap(order *o1, order *o2) {
    order temp_order;
    temp_order.demand = o1->demand;
    temp_order.width = o1->width;

    o1->demand = o2->demand;
    o1->width = o2->width;

    o2->demand = temp_order.demand;
    o2->width = temp_order.width;
}

void orders_quicksort_by_desc_width(order **orders, int order_count) {
    int i, j, pivot;

    if (order_count < 2) {
        return;
    }

    pivot = orders[order_count / 2]->width;

    for (i = 0, j = order_count - 1; ; i++, j--) {
        while (orders[i]->width > pivot) {
            i++;
        }
        while (orders[j]->width < pivot) {
            j--;
        }

        if (i >= j) {
            break;
        }

        order_swap(orders[i], orders[j]);
    }

    orders_quicksort_by_desc_width(orders, i);
    orders_quicksort_by_desc_width(orders + i, order_count - i);
}
