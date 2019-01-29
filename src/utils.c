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

#include "utils.h"

#if defined(__unix__)
    #include <sys/types.h>
    #include <sys/stat.h>
#elif defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#else
    #error "OS not supported"
#endif

int get_lines_number(FILE *file) {
    int lines;
    char c;

    lines = 0;
    fseek(file, 0, SEEK_SET);

    while (!feof(file)) {
        c = fgetc(file);
        if(c == '\n') {
            lines++;
        }
    }

    fseek(file, 0, SEEK_SET);

    return lines;
}

bool double_arrays_equals(double *a, double *b, int n) {
    int i;

    for (i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

bool double_matrix_contains_array(double **matrix, int n, double *array, int column_size) {
    int i;

    for (i = 0; i < n; i++) {
        if (double_arrays_equals(matrix[i], array, column_size)) {
            return true;
        }
    }

    return false;
}

bool is_file_exists(const char *file_name) {
#if defined(__unix__)
    struct stat st;
#elif defined(_WIN32) || defined(_WIN64)
    DWORD dw_attrib;
#else
    #error "OS not supported"
#endif

#if defined(__unix__)
    if (stat(file_name, &st) == 0) {
        return S_ISREG(st.st_mode);
    }
    return false;
#elif defined(_WIN32) || defined(_WIN64)
    dw_attrib = GetFileAttributesA(file_name);
    if (dw_attrib != INVALID_FILE_ATTRIBUTES &&
        dw_attrib != FILE_ATTRIBUTE_DIRECTORY) {
        return true;
    }
#endif

    return false;
}
