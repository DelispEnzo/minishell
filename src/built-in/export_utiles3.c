#include"built_in.h"

int creat_export_env_normv2(struct data* data, char **tmp, char **res)
{
    int i;

    i = 0;
    while (data->env[i])
    {
        res[i] = check_equal(tmp[i]);
        if(!res[i])
        {
            free_tab(tmp);
            tmp = NULL;
            write(2, "malloc fail\n", 13);
            return(1);
        }
        i++;
    }
    res[i] = NULL;
    return(0);
}

int creat_export_env(struct data* data)
{
    char** tmp;
    char** res;

    res = NULL;
    tmp = malloc(sizeof(char *) * (ft_tab_len(data->env) + 1));
    if(!tmp)
    {
        write(2, "malloc fail\n", 13);
        return(1);
    }
    if(creat_export_env_norm(data, tmp) != 0)
        return(1);
    res = malloc(sizeof(char *) * (ft_tab_len(data->env) + 1));
    if(!res)
    {
        free_tab(tmp);
        tmp = NULL;
        write(2, "malloc fail\n", 13);
        return(1);
    }
    if(creat_export_env_normv2(data, tmp, res) != 0)
        return(1);
    if(tmp)
        free_tab(tmp);
    data->export_tab = res;
    return(0);
}

void print_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        printf("%s\n", tab[i]);
        i++;
    }
    return;
}

void while_add_env(char *tmp, char *value_in_tab, char** old_tab, char *str, char **new_tab)
{
    int i;
    int j;
    int copied;

    copied = 0;
    i = ft_tab_len(old_tab);
    j = 0;
    while (j < i)
    {
        if(tmp)
            value_in_tab = get_before_equal_v2(old_tab[j]);
        if(tmp != NULL && value_in_tab != NULL && ft_strcmp(value_in_tab, tmp) == 0)
        {
            copied++;
            new_tab[j] = ft_strdup(str);
        }
        else
            new_tab[j] = ft_strdup(old_tab[j]);
        if(value_in_tab)
            free(value_in_tab);
        j++;
    }
    if(copied == 0)
    {
        new_tab[j] = ft_strdup(str);
        new_tab[j + 1] = NULL;
    }
    else
        new_tab[j] = NULL;
}

char **add_to_env_tab(char **old_tab, char *str, char* tmp)
{
    char **new_tab;
    char* value_in_tab;
    int i;

    i = 0;
    value_in_tab = NULL;
    new_tab = NULL;
    if (old_tab)
        i = ft_tab_len(old_tab);
    new_tab = malloc(sizeof(char *) * (i + 2));
    if (!new_tab)
        return (old_tab);
    while_add_env(tmp, value_in_tab, old_tab, str, new_tab);
    if (old_tab)
    {
        free_tab(old_tab);
        old_tab = NULL;
    }
    return (new_tab);
}
