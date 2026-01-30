#include"built_in.h"

char **add_to_env_tab_cd(char **old_tab, char *str)
{
    int i;
    char **new_tab;
    int j;

    i = 0;
    j = 0;
    if (old_tab)
    {
        while (old_tab[i])
            i++;
    }
    new_tab = malloc(sizeof(char *) * (i + 1));
    if (!new_tab)
        return (old_tab);
    while (j < i)
    {
        if(ft_strncmp(old_tab[j], "OLDPWD=", 7) == 0)
            new_tab[j] = ft_strdup(str);
        else
            new_tab[j] = old_tab[j];
        j++;
    }
    new_tab[j] = NULL;
    if (old_tab)
        free(old_tab);
    return (new_tab);
}

void ft_cd(char** args, struct data* data)
{
    char* path_cd;
    char* old_pwd;
    char* tmp;

    tmp = getcwd(NULL, 0);
    old_pwd = ft_strjoin("OLDPWD=", tmp);
    path_cd = NULL;
    if(args[1])
        path_cd = args[1];
    if(!args[1])
        path_cd = getenv("HOME");
    if(chdir(path_cd) != 0)
    {
        perror("cd");
        free(tmp);
        free(old_pwd);
        return;
    }
    else
    {
        data->env = add_to_env_tab_cd(data->env, old_pwd);
        if(data->export_tab)
            data->export_tab = add_to_env_tab_cd(data->export_tab, old_pwd);
    }
    return;
}
