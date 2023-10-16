#include "shell.h"

/**
 *custom_buitin_environ - shows environment where the shell run
 * @data: struct.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int custom_builtin_environ(data_of_program *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	if (data->tokens[1] == NULL)
		custom_env_print(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (data->tokens[1][i] == '=')
			{
				var_copy = str_copy(custom_env_get_key(cpname, data));
				if (var_copy != NULL)
					custom_env_set_key(cpname, data->tokens[1] + i + 1, data);

				custom_env_print(data);
				if (custom_env_get_key(cpname, data) == NULL)
				{
					custom_print(data->tokens[1]);
					custom_print("\n");
				}
				else
				{
					custom_env_set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_pair_environ - the new pair environment.
 * @data: struct for the program's data
 * Return: zero if sucess.
 */
int builtin_pair_environ(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	custom_env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unpaired_environ - the newly unpaired environment
 * @data: struct for the program's data'
 * Return: zero if success.
 */
int builtin_unpaired_environ(data_of_program *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	custom_env_remove_key(data->tokens[1], data);

	return (0);
}
