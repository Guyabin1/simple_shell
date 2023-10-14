#include "shell.h"

/**
 * free_data_recurring - free the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_data_recurring(data_of_program *data)
{
	if (data->tokens)
		custom_free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_data_all - free all field of the data
 * @data: struct data
 * Return: Nothing
 */
void free_data_all(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_data_recurring(data);
	custom_free_array_of_pointers(data->env);
	custom_free_array_of_pointers(data->alias_list);
}

/**
 * custom_free_array_of_pointers - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void custom_free_array_of_pointers(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
