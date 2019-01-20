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
