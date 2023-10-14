#include "shell.h"
/**
 * main - initialize the variables of the program to be printed
 * @argc: number of values received from the cmd
 * @argv: values received from the cmd
 * @env: number of values received from the cmd
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	int_data(data, argc, argv, env);

	signal(SIGINT, handle_control_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	separate_infi(prompt, data);
	return (0);
}

/**
 * handle_control_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void handle_control_c(int opr UNUSED)
{
	custom_print("\n");
	custom_print(PROMPT_MSG);
}

/**
 * int_data - initialize the struct 
 * @data: pointer to the struct.
 * @argv: array of arguments pased to the program execution
 * @env: environment pased to the program execution
 * @argc: number of values received from the cmd
 */
void int_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			custom_printe(data->program_name);
			custom_printe(": 0: Can't open ");
			custom_printe(argv[1]);
			custom_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_copy(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * separate_infi - its a infinite loop that shows the prmt
 * @prompt: prmt
 * @data: its an ifinite data
 */
void separate_infi(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		custom_print(prompt);
		error_code = string_len = get_line(data);

		if (error_code == EOF)
		{
			free_data_all(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			expanded_alias_simple(data);
			expanded_varable_simple(data);
			custom_tokenize(data);
			if (data->tokens[0])
			{
				error_code = custom_execute(data);
				if (error_code != 0)
					custom_print_error(error_code, data);
			}
			free_data_recurring(data);
		}
	}
}
