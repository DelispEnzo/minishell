#include"built_in.h"

void norminette_tricks(char *res, char *key, char *value, int i)
{
    int j;

    j = 0;
    while (key[j])
        res[i++] = key[j++];
    res[i++] = '=';
    res[i++] = '"';
    j = 0;
    while (value[j])
        res[i++] = value[j++];
    res[i++] = '"';
    res[i] = '\0';
}

void fill_res(char *res, char *key, char *value)
{
    int i;
    int j;
    char *export;

    i = 0;
    j = 0;
    if (!res || !key || !value)
        return;
    export = ft_strdup("export ");
    if(!export)
    {
        write(2, "malloc fail\n", 13);
        return;
    }
    while (export[j])
        res[i++] = export[j++];
    norminette_tricks(res, key, value, i);
    free(export);
}

int check_equal_norm(char*str, char* tmp)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '=')
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';
    return(i);
}

void swap_tab(char* tmp, char**tab, int x, int i)
{
    tmp = tab[x];
    tab[x] = tab[i];
    tab[i] = tmp;
}

void sort_tab(char **tab)
{
    char* tmp;
    int i;
    int y;
    int x;

    tmp = NULL;
    i = 0;
    x = 0;
    y = 0;
    if(ft_strncmp("export ", tab[0], 8))
        y = 7;
    while (tab[x])
    {
        i = x;
        while (tab[i])
        {
            if(tab[i][y] < tab[x][y])
                swap_tab(tmp, tab, x, i);
            i++;
        }
        x++;
    }
    return;
}