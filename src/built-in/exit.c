#include"built_in.h"
// >> exit et cree le dossier
// > exit et cree e dossier 
// | exit pas
// < si le directory existe il exite sinon il met no such file directory
// << ouvre un ear doc et exite lorsque le ear doc est fermer
// si l'argument n'es pas un nombre ou il est trop grand alors le code d'erreur est 2 et il exite mais il marque "numeric argument required",  code d'erreur = 2
// si les arg sont + de 1 "too many arguments" et exit pas , code d'erreur = 1
// -9223372036854775809 exit min
// 9223372036854775807 exit max
// /!\fonction pas tester /!\/

long long int ft_exit(char** argv)
{
    long long int exit_code;


    exit_code = 0;
    if(argv[1])
    {
        if(argv[2])// plusieur arg
        {
            if(ft_isdigit_line(argv[1]) == 1)
            {
                exit_code = 2;
                printf("exit\n");
                printf("exit: %s: numeric argument required \n", argv[1]);
                return(exit_code);
            }
            else
            {
                exit_code = 1;
                printf("exit\n");
                printf(" exit: too many arguments \n"); // dans se cas on EXIT PAS !!!
                return(exit_code) ;
            }
        }
        else // un seul arg
        {
            if(ft_isdigit_line(argv[1]) == 0) // regarder la valeur de retour de is_digit
            {
                exit_code = ft_atoi_long_long(argv[1]); //coder atoi pour les long long int
                if(exit_code > 256)
                    exit_code = exit_code % 256;
                printf("exit\n");
                return(exit_code);
            }
            else if(ft_isdigit_line(argv[1]) == 1)
            {
                exit_code = 2;
                printf("exit\n");
                printf("exit: %s: numeric argument required \n", argv[1]);
                return(exit_code);
            }
        }
    }
    printf("exit\n");
    return(exit_code);
}


