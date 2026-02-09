#include"built_in.h"

char **replace_env(char**old_env, char* str)
{
    char **new_env;
    int i;
    int y;

    y = 0;
    i = 0;
    if (!old_env)
        return (NULL);
    new_env = malloc(sizeof(char*) * (ft_tab_len(old_env) + 1));
    if(!new_env)
    {
        perror("malloc");
        return(NULL);
    }
    while (old_env && old_env[i])
    {
        replace_env_while(&y, i, old_env, str, new_env);
        i++;
    }
    new_env[y] = NULL;
    free_tab(old_env);
    return(new_env);
}

int change_two_env(struct data* data, char* tmp ,char **argv, int i)
{
    data->export_tab = replace_env(data->export_tab, tmp);
    if(!data->export_tab)
    {
        perror("malloc");
        free(tmp);
        return(1);
    }
    free(tmp);
    tmp = NULL;
    data->env = replace_env(data->env, argv[i]);
    if(!data->env)
    {
        perror("malloc");
        return(1);
    }
    return(0);
}

int change_export_env(char *tmp, struct data *data, char** argv, int i)
{
    tmp = ft_strjoin("export ", argv[i]);
    if (!tmp)
    {
        perror("malloc");
        return(1);
    }   
    data->export_tab = replace_env(data->export_tab, tmp);
    if(!data->export_tab)
    {
        free(tmp);
        perror("malloc");
        return(1);
    }
    free(tmp);
    return(0);
}
int while_unset(char **argv, struct data *data)
{
    int i;
    char* tmp;

    tmp = NULL;
    i = 1;
    while (argv[i])
    {
        tmp = is_inenv(argv[i], data->env);
        if(tmp != NULL)
        {
            if(change_two_env(data, tmp, argv, i) != 0)// il y a un egal
                return(1);  
        }
        else
        {
            if(change_export_env(tmp, data, argv, i) != 0) // sans egal
                return(1);
        }
        i++;
    }
    return(0);
}

int ft_unset(char **argv, struct data *data)
{
    int i;

    i = 0;
    if(!data->export_tab)
        if(creat_export_env(data) != 0)
            return(1);
    if(!argv[1])
        return(0);
    while (argv[i])
    {
        if(have_spaces(argv[i]) != 0)
            perror("unset");
        i++;
    }
    return(while_unset(argv, data));
}
