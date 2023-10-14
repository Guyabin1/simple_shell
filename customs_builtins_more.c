#include "shell.h"

/**
 * customs_builtin_exit - exit of the program with the status
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int customs_builtin_exit(data_of_program *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
				&& data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = custom_atoi(data->tokens[1]);
	}
	free_data_all(data);
	exit(errno);
}

/**
 * _builtin_command - change the current directory
 * @data: struct.
 * Return: zero if sucess, or otherwise else
 */ 
int _builtin_command(data_of_program *data)
{
	char *dir_home = custom_env_get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (compare_string(data->tokens[1], "-", 0))
		{
			dir_old = custom_env_get_key("OLDPWD", data);
			if (dir_old)
				error_code = _set_working_dir(data, dir_old);
			custom_print(custom_env_get_key("PWD", data));
			custom_print("\n");

			return (error_code);
		}
		else
		{
			return (_set_working_dir(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (_set_working_dir(data, dir_home));
	}
	return (0);
}

/**
 * _set_working_dir - set the working directory on the statements
 * @data: struct.
 * @new_dir: path to be set as work directory
 * Return: zero if sucess, or otherwise else
 */
int _set_working_dir(data_of_program *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!compare_string(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		custom_env_set_key("PWD", new_dir, data);
	}
	custom_env_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * custom_builtin_support - shows the environment where the shell is running
 * @data: struct
 * Return: zero if sucess, or otherwise declared.
 */
int custom_builtin_support(data_of_program *data)
{
	int i, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		custom_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (i = 0; mensajes[i]; i++)
	{
		length = custom_str_length(data->tokens[1]);
		if (compare_string(data->tokens[1], mensajes[i], length))
		{
			custom_print(mensajes[i] + length + 1);
			return (1);
		}
	}

	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * custom_builtin_alias - add, remove or show aliases
 * @data: struct.
 * Return: zero if sucess, or otherwise declared.
 */
int custom_builtin_alias(data_of_program *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
		return (custom_alias(data, NULL));

	while (data->tokens[++i])
	{
		if (counter_char(data->tokens[i], "="))
			alias_set(data->tokens[i], data);
		else
			custom_alias(data, data->tokens[i]);
	}

	return (0);
}
