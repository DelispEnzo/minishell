#include"built_in.h"

char *get_before_equal(char* str)
{
    int i;
    char* res;
    char* true_res;

    i = 0;
    true_res = NULL;
    res = NULL;
    while (str[i] && str[i] != '=')
        i++;
    if(str[i] == '\0')
        return(NULL);
    res =  malloc(sizeof(char) * (i + 1));
    if(!res)
        return(write(2, "malloc fail\n", 13), NULL);
    i = 0;
    while (str[i] && str[i] != '=')
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    true_res = ft_strjoin("export ", res);
    free(res);
    res = NULL;
    return(true_res);
}

char *get_before_equal_v2(char* str)
{
    int i;
    char* res;

    i = 0;
    res = NULL;
    while (str[i] && str[i] != '=')
        i++;
    if(str[i] == '\0')
        return(ft_strdup(str));
    res =  malloc(sizeof(char) * (i + 1));
    if(!res)
    {
        write(2, "malloc fail\n", 13);
        return(NULL);
    }
    i = 0;
    while (str[i] && str[i] != '=')
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return(res);
}

char *check_equal(char* str)
{
    char    *tmp;
    char    *value;
    char    *res;
    int     i;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    if (str[i] == '\0')
        return (ft_strjoin("export ", str));
    tmp = malloc(sizeof(char) * (i + 1));
    if (!tmp)
        return (NULL);
    i = check_equal_norm(str,tmp);
    value = ft_strdup(str + i + 1);
    if (!value)
        return (free(tmp), NULL);
    res = malloc(sizeof(char) * (ft_strlen(tmp) + ft_strlen(value) + 12));
    if (!res)
        return (free(tmp), free(value), NULL);
    fill_res(res, tmp, value);
    return (free(tmp), free(value), res);
}

int creat_export_env_norm(struct data *data, char **tmp)
{
    int i;

    i = 0;
    while (data->env[i])
    {
        tmp[i] = ft_strdup(data->env[i]);
        if(!tmp[i])
        {
            if(tmp)
                free_tab(tmp);
            tmp = NULL;
            write(2, "malloc fail\n", 13);
            return(1);
        }
        i++;
    }
    tmp[i] = NULL;
    return(0);
}

char *ft_strjoin_mod(char *s1, char *s2)
{
    size_t    i;
    size_t    j;
    char    *dest;

    j = 0;
    dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 3));
    if (!dest)
        return (NULL);
    i = 0;
    while (s1[i])
    {
        dest[i] = s1[i];
        i++;
    }
    dest[i] = '\"';
    i++;
    while (s2[j])
        dest[i++] = s2[j++];
    dest[i] = '\"';
    i++;
    dest[i] = '\0';
    return (dest);
}
