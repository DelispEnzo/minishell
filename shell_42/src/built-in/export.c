#include"built_in.h"

void write_str(char *s)
{
    int i = 0;
    if (!s)
        return;
    while (s[i])
    {
        write(1, &s[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

char **add_to_env_tab(char **old_tab, char *str)
{
    int i = 0;
    char **new_tab;
    if (old_tab)
    {
        while (old_tab[i])
            i++;
    }
    new_tab = malloc(sizeof(char *) * (i + 2));
    if (!new_tab)
        return (old_tab);
    int j = 0;
    while (j < i)
    {
        new_tab[j] = old_tab[j];
        j++;
    }
    new_tab[j] = ft_strdup(str);
    new_tab[j + 1] = NULL;
    if (old_tab)
        free(old_tab);
    return (new_tab);
}

int ft_export(struct token *tk, struct data *dt)
{
    struct token *tmp_tk;

    //verif;
    tmp_tk = tk;
    if (tk->next != NULL && ft_strcmp(tmp_tk->type, "arg") == 0)
        tmp_tk = tk->next;
    if (dt->env && dt->env[0])
    {
        //printf("ici %s\n", tmp_tk->next->type);
        if (ft_strcmp(tk->value, "export=") == 0)
        {
            return 1;
        }
        if (ft_strcmp(tk->value, "export") == 0 && (tk->next == NULL || ft_strcmp(tk->next->type, "arg") != 0)) // affiche toute les variables d'environnement ajoute
        {
            // calcule la longueur des deux tableaux (env+export_tab)
            int i = 0, j = 0;
            while (dt->env && dt->env[i])
                i++;
            while (dt->export_tab && dt->export_tab[j])
                j++;
            // malloc un tableau de la taille calcule et le remplir des valeur de env puis des valeur d'export
            char **tmp_tab = malloc(sizeof(char *) * (i + j + 1));
            if (!tmp_tab)
            {
                // return
                return 1;
            }
            // remplir le nouveau tableau
            i = 0;
            //printf("1\n");
            while (dt->env[i])
            {
                tmp_tab[i] = ft_strdup(dt->env[i]);
                i++;
            }
            j = 0;
            while(dt->export_tab && dt->export_tab[j])
                tmp_tab[i++] = ft_strdup(dt->export_tab[j++]);
            tmp_tab[i] = NULL;
            // trie le tableau finale
            i = 0;
            char *swap;
            //printf("1\n");
            while (tmp_tab[i])
            {
                j = i + 1;
                while (tmp_tab[j])
                {
                    if (ft_strcmp(tmp_tab[i], tmp_tab[j]) > 0)
                    {
                        swap = tmp_tab[i];
                        tmp_tab[i] = tmp_tab[j];
                        tmp_tab[j] = swap;
                    }
                    j++;
                }
                i++;
            }
            // afficher le tableau trie dans l'ordre
            i = 0;
            while(tmp_tab[i])
            {
                write_str(tmp_tab[i]);
                i++;
            }
            free_tab(tmp_tab);
            printf("DEBUG: Bloc Affichage\n");
        }
        else if (ft_strcmp(tk->value, "export") == 0 && (tk->next && ft_strcmp(tk->next->type, "arg") == 0))
        {
            struct token *count_ptr = tk->next;
            int count_arg = 0;
            while (count_ptr && ft_strcmp(count_ptr->type, "arg") == 0)
            {
                count_arg++;
                count_ptr = count_ptr->next;
            }
            char **arg_tab = malloc(sizeof(char *) * (count_arg + 1));
            if (!arg_tab)
                return (1);
            int k = 0;
            struct token *current_arg = tk->next; 
            while (k < count_arg)
            {
                arg_tab[k] = ft_strdup(current_arg->value);
                current_arg = current_arg->next;
                k++;
            }
            arg_tab[k] = NULL;
            // logique d'ajout/remplacement
            k = 0;
            while (arg_tab[k])
            {
                char *equal_pos = ft_strchr(arg_tab[k], '=');
                if (equal_pos)
                {
                    int exists = 0;
                    int env_idx = 0;
                    int name_len = equal_pos - arg_tab[k];
                    while (dt->env && dt->env[env_idx])
                    {
                        // vrif nom + =
                        if (ft_strncmp(dt->env[env_idx], arg_tab[k], name_len) == 0 
                            && dt->env[env_idx][name_len] == '=')
                        {
                            free(dt->env[env_idx]);
                            dt->env[env_idx] = ft_strdup(arg_tab[k]);
                            exists = 1;
                            break;
                        }
                        env_idx++;
                    }
                    if (!exists)
                        dt->env = add_to_env_tab(dt->env, arg_tab[k]);
                }
                k++;
            }
            free_tab(arg_tab);
            printf("DEBUG: Bloc Ajout terminé avec succès\n");
        }
        // maj de tk apres export pour faire en sorte que auqnd ca return tk soit deja sur la prochaine commande ou l'autre type
        // jsp si c necessaire hassoul
        while (tk->next && ft_strcmp(tk->next->type, "arg") == 0)
            tk = tk->next;
    }
    return 0;
}
