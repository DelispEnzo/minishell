#include"built_in.h"

int ft_pwd(void) // Donne le chemin d'acess au dossier acctuel 
{
    char *pwd;

    pwd = getcwd(NULL, 0); // getcwd fait tout tout seul et revoie NULL si il fail
    if(pwd == NULL)
        return(printf("no such file or directory"), 1);
    else
        printf("%s\n", pwd);
    free(pwd);
    return(0);
}

// int main(void)
// {
//     ft_pwd();
//     return(0);
// }
