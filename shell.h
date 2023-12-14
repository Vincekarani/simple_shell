#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRINGTOK 0

#define HISTORY_FILE	"simple_shell_history"
#define HISTORY_MAX	4096
/* _atoi.c */
int _atoi(char *s);

extern char **environ;

/**
 * struct liststring - singly linked list
 * @number: the number's field
 * @string: string
 * @next: pointer to the next node
 */
typedef struct liststring
{
	int number;
	char *string;
	struct liststring *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function's
 * information, allowing uniform
 * prototype for function pointer struct
 * @arg: a string generated from getline that contains arguements
 * @argarr: an array of strings generated from argument
 * @path: string path for the current command
 * @argcnt: the argument's count
 * @line_cnt: the error's count
 * @err_number: the error's code for exit()s
 * @linecnt_flag: if on count this line's input
 * @f_name: program's filename
 * @env: linked list of local copy's environ
 * @environ: custom modified copy of environment from linked list
 * environment 
 * @history: history node
 * @alias: alias node
 * @environ_changed: if environment was changed
 * @status: return status of the last executed command
 * @command_buf: address of pointer to command_buf, on if a chain.
 * command_buf_type: COMMAND_type ||, &&, ;
 * @readfield: field from which to read line input
 * @histo_cnt: history line's number count
 */
typedef struct passinfo
{
	char *arg;
	char **argarr;
	char *path;
	int argc;
	unsigned int line_cnt;
	int err_number;
	int linecnt_flag;
	char *f_name;
	list_t *environ;
	list_t *history;
	list_t *alias;
	char **env;
	int environ_changed;
	int status;

	char **command_buf; 
	/* pointer to command ; chain buffer, for memory mangement */
	int command_buf_type; 
	/* COMMAND_type ||, &&, ; */
	int readfd;
	int histo_count;
} infor_t;

#define INFOR_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @fun: the function
 */
typedef struct builtin
{
	char *type;
	int (*fun)(infor_t *);
}
builtin_table;

/* _shloop.c */
int hsh(infor_t *, char **);
int find_builtin(infor_t *);
void find_command(infor_t *);
void fork_command(infor_t *);

/* _parser.c */
int is_command(infor_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(infor_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* _errors.c */
void _iputs(char *);
int _iputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* _string.c */
int _stringlength(char *);
int _stringcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* _string1.c */
char *_stringcpy(char *, char *, int);
char *_stringedup(const char *);
void _puts(char *);
int _putchar(char);

/* _exits.c */
char *_stringcpy(char *, char *, int);
char *_stringcat(char *, char *, int);
char *_stringchr(char *, char);

/* _token.c */
char **stringtow(char *, char *);
char **stringtow2(char *, char);

/* _realloc.c */
char *_memoset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* _memory.c */
int cfree(void **);

/* _errors1.c */
int _erratoi(char *);
void print_error(infor_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* _builtin.c */
int _myexit(infor_t *);
int _mycurrentdirectory(infor_t *);
int _myhelp(infor_t *);

/* _builtin1.c */
int _myhistory(infor_t *);
int _myalias(infor_t *);

/*_getline.c */
size_t get_input(infor_t *);
int _getline(infor_t *, char **, size_t *);
void signintHandler(int);

/* _getinfo.c */
void clear_infor(infor_t *);
void set_infor(infor_t *, char **);
void free_infor(infor_t *, int);

/* _environ.c */
char *_getenviron(infor_t *, const char *);
int _myenviron(infor_t *);
int _mysetenviron(infor_t *);
int _myunsetenviron(infor_t *);
int populate_environ_list(infor_t *);

/* _getenviron.c */
char **get_environ(infor_t *);
int _unsetenviron(infor_t *, char *);
int _setenviron(infor_t *, char *, char *);

/* _history.c */
char *get_history_file(infor_t *infor);
int write_history(infor_t *infor);
int read_history(infor_t *infor);
int build_history_list(infor_t *infor, char *buf, int linecnt);
int renum_history(infor_t *infor);

/* _lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* _lists_1.c */
size_t list_len(const list_t *);
char **list_to_strns(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* _variables.c */
int is_chain(infor_t *, char *, size_t *);
void check_chain(infor_t *, char *, size_t *, size_t, size_t);
int replace_alias(infor_t *);
int replace_variables(infor_t *);
int replace_string(char **, char *);

#endif
