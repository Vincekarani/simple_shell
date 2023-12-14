#ifndef _SHELL_H_
#define _SHELL_H_

/*
 * File: shell.h
 * Author: Vincent Karani Ouru in
 * collaboration with Nancy Njeri
 */

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
external char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hiatory;

/**
 * struct list_s - struct type newly defining a linked list.
 * @directory: A path directory.
 * @next: Another struct list_s' pointer.
 */
typedef struct list_s
{
	char *directory;
	struct list_s *next;
 list_t;

/**
 * struct builtin_s - struct type newly defining builtin commands.
 * @name: The name of the builtin command.
 * @func: A pointer's function to the builtin function of command.
 */
typedef struct builtin_s
{
	char *name;
	int (*func)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A struct newly defining aliases.
 * @name: The alias' name.
 * @value: The alias' value.
 * @next: Another struct's pointer alias_s.
 * */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t _getline(char **linepointer, size_t *m, FILE *stream);
void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size);
char **_stringtok(char *line, char *delim);
char *get_location(char *command);
list_t *get_path_directory(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int number);

/* Input Helpers */
void handle_line(char **line, size_t read);
void variable_replacement(char **args, int *execute_return);
char *get_arguments(char *line, int *execute_return);
int call_args(char **args, char **front, int *execute_return);
int run_arguments(char **args, char **front, int *execute_return);
int handle_arguments(int *execute_return);
int check_arguments(char **args);
void free_arguments(char **args, char **front);
char **replace_aliases(char **args);

/* String functions */
int _stringlength(const char *s);
char *_stringcat(char *dest, const char *src);
char *_stringncat(char *dest, const char *src, size_t n);
char *_stringcpy(char *dest, const char *src);
char *_stringchr(char *s, char c);
int _stringspn(char *s, char *accept);
int _stringcmp(char *s1, char *s2);
int _stringcmp(const char *s1, const char P,,*s2, size_t n);
int _atoi(char *s)
/* Builtins */
int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_environ(char **args, char __attribute__((__unused__)) **front);
int shellby_setenviron(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenviron(char **args, char __attribute__((__unused__)) **front);
int shellby_currentdirectory(char **args, char __attribute__((__unused__)) **front);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **_copyenviron(void);
void free_environ(void);
char **_getenviron(const char *variable);

/* Error Handling */
int create_error(char **args, int error);
char *error_environ(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_currentdiroctory(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

void help_all(void);
void help_alias(void);
void help_current_directory(void);
void help_exit(void);
void help_help(void);
void help_environ(void);
void help_setenviron(void);
void help_unsetenviron(void);
void help_history(void);

int proc_file_commands(char *file_path, int *execute_return);
#endif
