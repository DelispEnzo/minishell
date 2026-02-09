#include"built_in.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int if_equal(int i, char **argv, struct data *data, char *tmp)
{
    char *res;

    res = check_equal(argv[i]);
    if(!res)
        return(write(2, "malloc fail\n", 13), 1);
    data->export_tab = add_to_env_tab(data->export_tab ,res, tmp);
    if(!data->export_tab)
    {
        write(2, "malloc fail\n", 13);
        free(tmp);
        free(res);
        return(1);
    }
    free(tmp);
    tmp = NULL;
    tmp = ft_strdup(argv[i]);
    data->env = add_to_env_tab(data->env, argv[i], tmp);
    if(!data->export_tab)
    {
        write(2, "malloc fail\n", 13);
        free(tmp);
        free(res);
        return(1);
    }
    free(res);
    res = NULL;
    return(0);
}

int if_not_equal(int i, char **argv, struct data *data, char *tmp)
{
    char* res;

    tmp = ft_strjoin("export ", argv[i]);
    res = check_equal(argv[i]);
    if(!res)
    {
        write(2, "malloc fail\n", 13);
        return(1);
    }
    data->export_tab = add_to_env_tab(data->export_tab ,res, tmp);
    if(!data->export_tab)
    {
        write(2, "malloc fail\n", 13);
        if(tmp)
            free(tmp);
        if(res)
            free(res);
        return(1);
    }
    free(res);
    res = NULL;
    return(0);
}

int while_ft_export(char **argv, int i, char *tmp, struct data *data)
{
    if(have_spaces(argv[i]) != 0)
        perror("export");
    if(argv[i][0] == '=')
    {
        write(2, "minishell: export: ", 15);
        ft_putstr_fd(argv[i], 2);
        write(2, ": not a valid  identifier\n", 25);
        return(1);
    }
    tmp = get_before_equal(argv[i]); // Copie tout avant un '='
    if(tmp != NULL) // si se n'est pas dans env , ou qu'il y a un egal
    {
        if(if_equal(i, argv, data, tmp) != 0)
            return(1);
    }
    else // il n'y a  pas '='
    {
        if(if_not_equal(i, argv, data, tmp) != 0)
            return(1);
    }
    if(tmp)
    {
        free(tmp);
        tmp = NULL;
    }
    return(0);
}

int ft_export(char** argv, struct data *data)
{
    int i;
    char* tmp;

    i = 1;
    tmp = NULL;
    if(!data->export_tab)
    {
        if(creat_export_env(data) != 0)
            return(1);
        sort_tab(data->export_tab);
    }
    if(!argv[1])
    {
        print_tab(data->export_tab);
        return(0);
    }
    while (argv[i])
    {
        if(while_ft_export(argv, i, tmp, data) != 0)
            return(1);
        i++;
    }
    sort_tab(data->export_tab);
    return(0);
}
