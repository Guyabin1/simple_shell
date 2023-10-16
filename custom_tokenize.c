#include "shell.h"
/**
 * custom_tokenize - the function that puts aside the string using a delim
 * @data: a pointer.
 * Return: an array of the different parts of the string
 */
void custom_tokenize(data_of_program *data)
{
	char *delimiter = " \t";
	int i, j, counter = 2, length;

	length = custom_str_length(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (i = 0; data->input_line[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (data->input_line[i] == delimiter[j])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = str_copy(custom_strtok(data->input_line, delimiter));
	data->command_name = str_copy(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = str_copy(custom_strtok(NULL, delimiter));
	}
}
