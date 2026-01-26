#include"built_in.h"
// >> exit et cree le dossier
// > exit et cree e dossier 
// | exit pas
// < si le directory existe il exite sinon il met no such file directory
// << ouvre un ear doc et exite lorsque le ear doc est fermer
// si l'argument n'es pas un nombre ou il est trop grand alors le code d'erreur est 2 et il exite mais il marque "numeric argument required",  code d'erreur = 2
// si les arg sont + de 1 "too many arguments" et exit pas , code d'erreur = 1

// /!\fonction pas tester /!\/

int ft_exit(struct token *tokens)
{
    struct token *element;
    unsigned int exit_code;


    element = tokens;
    exit_code = 0;
    // chek le segond neud et le gere
    if(element->next != NULL)
    {
        element = element->next;
        tmp = tmp->next;
        if(tmp->next != NULL)// plusieur arg
        {
            tmp = tmp->next;
            if(is_separator(tmp->value) == 1 && ft_isdigit(element->value) == 1)
            {
                exit_code = ft_atoi_unsigned(element->value); //coder atoi pour les unsigned
                if(tmp > 256)
                    exit_code = exit_code % 256;
                printf("exit\n");
                // tout free ici
                return(exit_code);
            }
            else if(ft_isdigit(element->value) == 0)
            {
                exit_code = 2;
                printf("exit\n");
                printf("exit: %s: numeric argument required \n", element->value);
                return(exit_code)
            }
            else
            {
                exit_code = 1;
                printf("exit\n");
                printf(" exit: too many arguments \n");
                return(exit_code) 
            }
        }
        else // un seul arg
        {
            if(ft_isdigit(element->value) == 1 && element->type == "arg") // regarder la valeur de retour de is_digit
            {
                exit_code = ft_atoi_unsigned(element->value); //coder atoi pour les unsigned
                if(tmp > 256)
                    exit_code = exit_code % 256;
                printf("exit\n");
                return(exit_code);
            }
            else if(ft_isdigit(element->value) == 0 && (element->type == "arg" || element->type == "commande"))
            {
                exit_code = 2;
                printf("exit\n");
                printf("exit: %s: numeric argument required \n", element->value);
                return(exit_code)
            }
            else
            {
                printf("exit\n");
                return(exit_code);
            }
        }
    }
    else
    {
        printf("exit\n");
        return(exit_code);
    }
}


