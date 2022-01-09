#ifndef UTILS_H
#define UTILS_H

#include "utils/list.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * @brief Will run through the linked list until find a NULL pointer. 
 * 
 * @example for_each_item(i, l)
 *              printf("%d\n", i->value);
 * 
 * @param item Var that will be use for each iteration.
 * @param l The linked list.
 * 
 * TODO: Add more abstraction/polymorphism.
 */
#define for_each_item(item, l) \
    for (List * (item) = (l)->head; (item); (item) = (item)->next)

/**
 * @brief Go through all item of a given array.
 * 
 * @param item Var that will be use for each iteration.
 * @param array Array to go through.
 */
#define for_each(item, array)                          \
    for (int keep = 1, count = 0,                      \
        size = sizeof((array)) / sizeof(*(array));     \
        keep && count != size;                         \
        keep = !keep, ++count)                         \
        for (item = (array) + count; keep; keep = !keep)

static inline void utils_clear_terminal(void)
{
    fflush(stdout);
    system("clear||cls");
}

/**
 * @brief Check weather the file exists or not.
 * 
 * @param fname Path to file.
 * @return true The file exists.
 * @return false The file does not exist.
 */
static inline bool utils_file_exists(const char *fname)
{
    if (access(fname, F_OK))
        return true;
    else
        return false;
}

#endif //UTILS_H
