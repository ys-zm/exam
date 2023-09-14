#include "htmltag.h"

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

bool    ft_strncmp(char *str1, char *str2, int n)
{
    int i = 0;
    while (str1 && str2 && str1[i] && str2[i] && n)
    {
        if (str1[i] != str2[i])
            return (false);
        i++;
        n--;
    }
    return (true);
}

t_list  *new_node(char *str)
{
    int len = 0;
    t_list *new;

    if (*str == '<')
        str++;
    while (str[len] != '>')
        len++;
    new  = malloc(sizeof(t_list) * 1);
    new->tag = ft_substr(len, str);
    if (ft_strncmp(new->tag, "img", 3) || ft_strncmp(new->tag, "br", 2))
    {
        free(new->tag);
        free(new);
        return (NULL);
    }
    new->next = NULL;
    return (new);
}

t_list    *ft_push_to_list(t_list *list, char *str)
{
    t_list *lst;
    t_list *save;

    save = list;
    lst = list;
    if (!lst)
        save = new_node(str);
    else
    {
        while (lst->next != NULL)
            lst = lst->next;
        lst->next = new_node(str);
    }
    return (save);
}

bool    ft_is_op_tag(char *str)
{
    int     i = 0;

    while (str[i] && str[i] != '<')
        i++;
    if (str[i] == '\0')
        return (false);
    i++;
    if (str[i] == '/')
        return (false);
    while (str[i] && str[i] != '>')
        i++;
    if (str[i] && str[i] == '>')
        return (true);
    else
        return (false);
}

bool    ft_is_cl_tag(char *str)
{
    int i = 0;

    while (str[i] && str[i] != '<')
        i++;
    if (str[i] == '\0')
        return (false);
    i++;
    if (str[i] != '/')
        return (false);
    else
        i++;
    while (str[i] && str[i] != '>')
        i++;
    if (str[i] && str[i] == '>')
        return (true);
    else
        return (false);
}

t_list    *ft_pop_2(t_list *list)
{
    t_list *next;
    t_list  *prev;
    
    if (! list)
        return (NULL);
    prev = list;
    next = list->next;
    if (next == NULL)
    {
        free(prev->tag);
        free(prev);
        return (NULL);
    }
    while (next->next)
    {
        prev = next;
        next = next->next;
    }
    // free(next->tag);
    free(next);
    prev->next = NULL;
    next = NULL;
    return (list);
}

t_list    *ft_pop(t_list *list)
{
    t_list *next;
    t_list  *prev;
    t_list  *save;
    
    save = list;
    next = list;
    if (!next)
        next = NULL;
    while (next != NULL)
    {
        prev = next;
        next = next->next;
        if (next == NULL)
            break ;
    }
    // free(next->tag);
    free(next);
    prev->next = NULL;
    next = NULL;
    return (save);
}

bool    ft_if_match(char *str, t_list *list)
{
    int len = 0;
    char    *tag;

    if (!list)
        return (false);
    while (*str && *str != '<')
        str++;
    str++;
    str++;
    while (str[len] && str[len] != '>')
        len++;
    tag = ft_substr(len, str);
    while (list && list->next != NULL)
        list = list->next;
    if (ft_strncmp(list->tag, tag, len))
        return (true);
    return (false);
}

bool    ft_check(char *str)
{
    int     i = 0;
    t_list  *list;

    list = NULL;
    while (str && str[i])
    {
        if (ft_is_op_tag(str + i))
        {
            list = ft_push_to_list(list, &str[i]);
            while (str[i] != '>')
                i++;
            i++;
        }
        printf("str h: %s\n", str + i);
        if (ft_is_cl_tag(str + i))
        {
            printf("is closed, %s -- %s\n", str + i, list->tag);
            if (ft_if_match(str + i, list))
            {
                list = ft_pop_2(list);  
                while (str[i] && str[i] != '<')
                    i++;
                i += 2;
                while (str[i] && str[i] != '>')
                    i++;
                i++;
            }
            else
                return (false);
        }
    }
    if (list)
        return (false);
    else
        return (true);
}

// compile the file with: gcc -Wall -Wextra -Werror -fsanitize=address -g3 htmltag.c -o exe 
int main(int argc, char **argv)
{
    if (argc == 1)
        return (1);
    if (ft_check(argv[1]))
        printf("OK\n");
    else
        printf("Error\n");
    return (0);
}