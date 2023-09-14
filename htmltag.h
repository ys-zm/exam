#ifndef HTMLTAG_H
# define HTMLTAG_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_list
{
    char            *tag;
    struct s_list   *next;
}   t_list;

#endif