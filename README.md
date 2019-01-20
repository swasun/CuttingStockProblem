A simple program that computes the Cutting Stock Problem using the *glpk* library (https://en.wikipedia.org/wiki/GNU_Linear_Programming_Kit) (old school project, Algorithmic and Operations Reseach class, 2017).

## Dependency

On Debian, you can install *glpk* with the following command:
```bash
apt install libglpk-dev
```

Otherwise, this is the site https://www.gnu.org/software/glpk/ of the project and the repository http://cvs.savannah.gnu.org/viewvc/glpk/.

## Usage

```
mkdir bin && mkdir obj && make
./bin/cutting_stock <file_name>
```

## Using the code

```c
#include "order.h"
#include "column.h"
#include "cutting_stock.h"

#include <glpk.h>

int main(int argc, char **argv) {
    order **orders;
    int order_count, max_width, best_patterns_number;
    double **best_patterns, *pattern_demand_repartition, obj_value;

    glp_term_out(GLP_OFF);

    orders = NULL;
    pattern_demand_repartition = NULL;
    best_patterns = NULL;
    pattern_demand_repartition = NULL;

    if (!(orders = orders_read_from_file(argv[1], &order_count, &max_width))) {
        /* Error handling here */
        goto clean_up;
    }

    if (!(best_patterns = cutting_stock_compute_best_patterns(orders, order_count, max_width, &best_patterns_number))) {
        /* Error handling here */
        goto clean_up;
    }

    if (!(pattern_demand_repartition = cutting_stock_compute(best_patterns, best_patterns_number, orders, order_count, &obj_value))) {
        /* Error handling here */
        goto clean_up;
    }

    cutting_stock_print_solution(best_patterns, best_patterns_number, order_count, pattern_demand_repartition, obj_value, orders, order_count, stdout);

clean_up:
    free((void *)pattern_demand_repartition);
    columns_matrix_destroy(best_patterns, best_patterns_number);
    orders_destroy(orders, order_count);
    glp_free_env();
    return 0
}
```

## Experiments

On 100 orders:
```
./bin/cutting_stock res/instance1.txt 
Execution of the algorithm in 0.000662s.
Pattern { 2x45 } x 48.500000
Pattern { 2x36 } x 100.750000
Pattern { 2x36 2x14} x 105.500000
Pattern { 1x36  2x31 } x 197.500000
Objective value : 452.250000
```

On 100 orders:
```
./bin/cutting_stock res/instance2.txt
Execution of the algorithm in 0.009895s.
[...]
Objective value : 858.214286
```

On 10000 orders:
```
./bin/cutting_stock res/instance3.txt
Execution of the algorithm in 0.267057s.
[...]
Objective value : 1065.000000
```

## Authors

* Charly LAMOTHE
* Doulkifouli ABDALLAH-ALI
