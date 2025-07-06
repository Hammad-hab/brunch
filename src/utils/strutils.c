#ifndef STRUTILS
#define STRUTILS
#include "../types.h"
#include<stdio.h>
#include<stdlib.h>

char *strtok_new(char *string, char const *delimiter)
{
    static char *source = NULL;
    char *p, *riturn = 0;
    if (string != NULL)
        source = string;
    if (source == NULL)
        return NULL;

    if ((p = strpbrk(source, delimiter)) != NULL)
    {
        *p = 0;
        riturn = source;
        source = ++p;
    } 
    return riturn;
}

char *concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); //+1 for the zero-terminator
    if (result != 0)
    {
        strcpy(result, s1);
        strcat(result, s2);
        return result;
    }
    exit(ALLOCERROR);
}

int starts_with(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}

#endif
