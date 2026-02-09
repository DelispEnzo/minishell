#include"built_in.h"

void replace_env_while(int *y,int i, char** old_env, char* str, char **new_env)
{
    char *tmp;

    tmp = get_before_equal_v2(old_env[i]);
    if(ft_strcmp(tmp , str) != 0)
    {
        new_env[(*y)] = ft_strdup(old_env[i]);
        (*y)++;
    }
    free(tmp);  
    tmp = NULL;
}

char* is_inenv(char *str, char** env)
{
    int i;
    char*tmp;

    tmp = NULL;
    i = 0;
    while (env[i])
    {
        tmp = get_before_equal_v2(env[i]);
        if(ft_strcmp(str, tmp) == 0)
        {
            if(tmp)
            {
                free(tmp);
                tmp = NULL;
            }
            return(ft_strjoin("export ", str));
        }
        if(tmp)
        {
            free(tmp);
            tmp = NULL;
        }
        i++;
    }
    return(NULL);
}