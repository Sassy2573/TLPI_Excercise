/*
 * @Author: sassy chenyinlin0429@gmail.com
 * @Date: 2024-08-16 15:07:24
 * @LastEditors: sassy chenyinlin0429@gmail.com
 * @LastEditTime: 2024-08-16 15:10:05
 * @FilePath: /chen/TLPI_Excercise/C_6/6-3.c
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int unsetenv(const char *name)
{
    extern char **environ;

    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) {
        errno = EINVAL;
        return -1;
    }

    size_t len = strlen(name);

    for (char **ep = environ; *ep != NULL; )
        if (strncmp(*ep, name, len) == 0 && (*ep)[len] == '=') {

            /* Remove found entry by shifting all successive entries
               back one element */

            for (char **sp = ep; *sp != NULL; sp++)
                *sp = *(sp + 1);

            /* Continue around the loop to further instances of 'name' */

        } else {
            ep++;
        }

    return 0;
}

int setenv(const char *name, const char *value, int overwrite)
{
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL ||
            value == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (getenv(name) != NULL && overwrite == 0)
        return 0;

    unsetenv(name);             /* Remove all occurrences */

    char *es = malloc(strlen(name) + strlen(value) + 2);
                                /* +2 for '=' and null terminator */
    if (es == NULL)
        return -1;

    strcpy(es, name);
    strcat(es, "=");
    strcat(es, value);

    return (putenv(es) != 0) ? -1 : 0;
}

// #ifdef TEST_IT

int main()
{
    if (putenv("TT=xxxxx") != 0)
        perror("putenv");

    system("echo '***** Environment before unsetenv(TT)'; "
            "printenv | grep ^TT");
    system("echo 'Total lines from printenv:' `printenv | wc -l`");

    unsetenv("TT");

    system("echo '***** Environment after unsetenv(TT)'; "
            "printenv | grep ^TT");
    system("echo 'Total lines from printenv:' `printenv | wc -l`");

    setenv("xyz", "one", 1);
    setenv("xyz", "two", 0);
    setenv("xyz2", "222", 0);

    system("echo '***** Environment after setenv() calls'; "
            "printenv | grep ^x");
    system("echo 'Total lines from printenv:' `printenv | wc -l`");

    exit(EXIT_SUCCESS);
}

// #endif