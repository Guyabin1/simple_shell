#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>


#include "macros.h"


/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for get_line
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of custom_tokenize input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;

int custom_str_length(char *string);
char *str_copy(char *string);
int compare_string(char *str1, char *str2, int number);
char *string_combined(char *string1, char *string2);
void string_backwards(char *string);
int custom_alias(data_of_program *data, char *alias);
char *_getalias(data_of_program *data, char *name);
int alias_set(char *alias_string, data_of_program *data);
int custom_builtin_environ(data_of_program *data);
int builtin_pair_environ(data_of_program *data);
int builtin_unpaired_environ(data_of_program *data);
char *custom_env_get_key(char *key, data_of_program *data);
int custom_env_set_key(char *key, char *value, data_of_program *data);
int custom_env_remove_key(char *key, data_of_program *data);
void custom_env_print(data_of_program *data);
int custom_execute(data_of_program *data);
int custom_buffer_add(char *buffer, char *str_to_add);
void expanded_alias_simple(data_of_program *data);
void expanded_varable_simple(data_of_program *data);
int custom_check_file(char *full_path);
char **custom_tokenize_find_path(data_of_program *data);
int search_for_program(data_of_program *data);
void custom_free_array_of_pointers(char **array);
void free_data_all(data_of_program *data);
void free_data_recurring(data_of_program *data);
void long_string(long number, char *string, int base);
int custom_atoi(char *s);
int counter_char(char *string, char *character);
int custom_printe(char *string);
int custom_print(char *string);
int custom_print_error(int errorcode, data_of_program *data);
int custom_main(int argc, char *argv[], char *env[]);
void handle_control_c(int opr UNUSED);
void int_data(data_of_program *data, int argc, char *argv[], char **env);
void separate_infi(char *prompt, data_of_program *data);
char *custom_strtok(char *line, char *delim);
void custom_tokenize(data_of_program *data);
int _builtins_list(data_of_program *data);
int customs_builtin_exit(data_of_program *data);
int _builtin_command(data_of_program *data);
int _set_working_dir(data_of_program *data, char *new_dir);
int custom_builtin_support(data_of_program *data);
int custom_builtin_alias(data_of_program *data);
int get_line(data_of_program *data);
int _customcheck_logic_ops(char *array_commands[], int i, char array_operators[]);



void int_data(data_of_program *data, int arc, char *argv[], char **env);
void separate_infi(char *prompt, data_of_program *data);
void handle_control_c(int opr UNUSED);
int get_line(data_of_program *data);
int check_logic_ops(char *array_commands[], int i, char array_operators[]);
void expand_variables(data_of_program *data);
void expanded_alias_simple(data_of_program *data);
int custom_buffer_add(char *buffer, char *str_to_add);
void custom_tokenize(data_of_program *data);
char *custom_strtok(char *line, char *delim);
int custom_execute(data_of_program *data);
int _builtins_list(data_of_program *data);
char **custom_tokenize_find_path(data_of_program *data);
int search_for_program(data_of_program *data);
void custom_free_array_of_pointers(char **directories);
void free_data_recurring(data_of_program *data);
void free_all_data(data_of_program *data);
int customs_builtin_exit(data_of_program *data);
int _builtin_command(data_of_program *data);
int _set_working_dir(data_of_program *data, char *new_dir);
int custom_builtin_support(data_of_program *data);
int custom_builtin_alias(data_of_program *data);
int custom_buitin_environ(data_of_program *data);
int builtin_set_env(data_of_program *data);
int builtin_unpaired_environ(data_of_program *data);
char *env_get_key(char *name, data_of_program *data);
int custom_env_set_key(char *key, char *value, data_of_program *data);
int env_remove_key(char *key, data_of_program *data);
void custom_env_custom_print(data_of_program *data);
int custom_print(char *string);
int custom_printe(char *string);
int custom_print_error(int errorcode, data_of_program *data);
int custom_str_length(char *string);
char *str_copy(char *string);

char *string_combined(char *string1, char *string2);
void string_backwards(char *string);
void long_string(long number, char *string, int base);
int custom_atoi(char *s);
int counter_char(char *string, char *character);
int custom_alias(data_of_program *data, char *alias);
char *_getalias(data_of_program *data, char *alias);
int alias_set(char *alias_string, data_of_program *data);


#endif
