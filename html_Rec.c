#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

char *ft_substr(int len, char *str)
{
    char *ret;
    int i = 0;    
    ret = malloc(sizeof(char ) * len + 1);
    while (i < len && str[i])
    {
        ret[i] = str[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

bool    ft_if_cl_tag(char *str)
{
    if (!str)
        return (false);
    if (*str && *str == '<')
        str++;
    if (*str && *str == '/')
        str++;
    else
        return (false);
    while (*str && *str != '>')
        str++;
    if (*str && *str == '>')
        return (true);
    else
        return (false);
}

bool    ft_if_op_tag(char *str)
{
    if (!str)
        return (false);
    if (*str && *str == '<')
        str++;
    else
        return (false);
    if (*str && *str == '/')
        return (false);
    else
        str++;
    while (*str && *str != '>')
        str++;
    if (*str && *str == '>')
        return (true);
    else
        return (false);
}

bool rec_check(char *str)
{
    char *tag_op;
    char *tag_cl;
    int len = 0;

    if (ft_if_op_tag(str))
    {
        //skip opening tag
        str++;
        while (str[len] && str[len] != ' ' && str[len] != '>')
            len++;
        tag_op = ft_substr(len, str);
        while (*str && *str != '>')
            str++;
        if (!strncmp(tag_op, "img", 3) || !strncmp(tag_op, "br", 3))
            return (true);
    }
    while (*str && *str != '<')
        str++;
    if (ft_if_cl_tag(str))
    {
        str++;
        str++;
        len = 0;
        while (str[len] && str[len] != ' ' && str[len] != '>')
            len++;
        tag_cl = ft_substr(len, str);
        printf("tag_cl: %s\n", tag_cl);
        printf("tag_op: %s\n", tag_op);
        if (strncmp(tag_cl, tag_op, len) != 0)
        {
            printf("f1\n");
            return (false);
        }
        else
        {
            while (*str && *str != '>')
                str++;
        }
    }
    if (ft_if_op_tag(str))
    {
        if (!rec_check(str))
        {
            printf("f2\n");
            return (false);
        }
        while (*str && *str != '>')
            str++;
        str++;
        while (*str && *str != '>')
            str++;
        str++;
    }
    return (true);
}

int main(int argc, char **argv)
{
    if (argc == 1)
        return (1);
    if (rec_check(argv[1]))
        printf("OK\n");
    else
        printf("Error\n");
    return (0);
}