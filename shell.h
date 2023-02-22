#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <signal.h>

#define FALSE 0
#define TRUE 1
#define NEITHER 2
#define MATCH 3
#define PREFIX 4
#define EXIT_SHELL 5
#define SKIP_FORK 6
#define DO_EXECVE 7

/**
 * struct Alias - singly linked list
 * @name: name of alias
 * @value: command that alias calls
 * @next: points to next node
 */
typedef struct Alias
{
	char *name;
	char *value;
	struct Alias *next;
} alias;

extern char **environ;

extern int status;

extern int line_num;

extern char *shell_name;

int command_manager(char **args);

int built_ins(char **args);

int and_or(char **args, char operator, int last_compare);

char *check_command(char **args);

int execute_command(char **args);

char *input_san(char *old_buf, size_t *old_size);

int input_err_check(char *ptr);

void err_message(char *arg0, char *arg1);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int _getline(char **line_ptr, size_t *n, int file);

char *check_for_vars(char *arg);

int _strlen(char *str);

char *_strdup(char *src);

char *str_concat(char *s1, char *s2);

int str_compare(char *s1, char *s2, int pref_or_match);

char *get_array_element(char **array, char *element_name);

char **make_array(char *str, char delim, char **if_sep);

int list_len(char **list, char *entry);

char **array_cpy(char **old_array, int new_size);

int free_array(char **args);

int _setenv(const char *name, const char *value);

int _unsetenv(const char *name);

int change_dir(char *name);

int alias_func(char **args, int free);

int free_aliases(alias *alias_ptr);

int check_if_alias(char **args, alias *alias_ptr);

int print_aliases(alias *alias_ptr);

int print_alias_value(char *arg, alias *alias_ptr);

int set_alias_value(char *arg, alias *alias_ptr, char *new_value);

int print_env(void);

char *_itoa(int n);

int _atoi(char *s);

#endif
