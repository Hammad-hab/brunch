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


char *strncpyutf8(char *dst, const char *src, size_t num)
{
    if (num)
    {
        size_t sizeSrc = strlen(src); // number of bytes not including null
        while (sizeSrc > num)
        {
            const char *lastByte = src + sizeSrc; // initially \0 at end

            while (lastByte-- > src)            // test previous chars
                if ((*lastByte & 0xC0) != 0x80) // utf8 start byte found
                    break;

            sizeSrc = lastByte - src;
        }
        memcpy(dst, src, sizeSrc);
        dst[sizeSrc] = '\0';
    }
    return dst;
}


#endif
