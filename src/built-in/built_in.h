#ifndef BUILT_IN_H
#define BUILT_IN_H

#include "../lexer/lexer.h"
#include "../libft/libft.h"
#include "../tokens/token.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct token;
struct data;
struct commandes;

char **add_to_env_tab(char **old_tab, char *str, char* tmp);
void while_add_env(char *tmp, char *value_in_tab, char** old_tab, char *str, char **new_tab);
void print_tab(char **tab);
int creat_export_env(struct data* data);
int creat_export_env_normv2(struct data* data, char **tmp, char **res);
void sort_tab(char **tab);
void swap_tab(char* tmp, char**tab, int x, int i);
int check_equal_norm(char*str, char* tmp);
void fill_res(char *res, char *key, char *value);
void norminette_tricks(char *res, char *key, char *value, int i);
char *ft_strjoin_mod(char *s1, char *s2);
int creat_export_env_norm(struct data *data, char **tmp);
char *check_equal(char* str);
int creat_export_env(struct data* data);
char *get_before_equal_v2(char* str);
char *get_before_equal(char* str);
void ft_cd(char** args, struct data* data);
int ft_export(char** argv, struct data *data);
int env(struct data *data);
int echo(char **argv);
int ft_pwd(void);
long long int ft_exit(char** argv);
int ft_unset(char **argv, struct data *data);
char* is_inenv(char *str, char** env);
void replace_env_while(int *y,int i, char** old_env, char* str, char **new_env);

#endif
