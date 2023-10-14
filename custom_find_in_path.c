#include "shell.h"

int custom_check_file(char *full_path);

/**
 * search_for_program - find a program in path
 * @data: a pointer to the program's data
 * Return: 0 if success, or else otherwise
 */

int search_for_program(data_of_program *data)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (custom_check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = string_combined(str_copy("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = custom_tokenize_find_path(data);

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; directories[i]; i++)
	{
		directories[i] = string_combined(directories[i], data->tokens[0]);
		ret_code = custom_check_file(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_copy(directories[i]);
			custom_free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	custom_free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * custom_tokenize_find_path - custom_tokenize the path in dir
 * @data: a pointer to the program's data
 * Return: array of path directories
 */

char **custom_tokenize_find_path(data_of_program *data)
{
	int i = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = custom_env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_copy(PATH);

	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			counter_directories++;
	}

	tokens = malloc(sizeof(char *) * counter_directories);

	i = 0;
	tokens[i] = str_copy(custom_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_copy(custom_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * custom_check_file - checks if exists a file.
 * @full_path: pointer to the full file name
 * Return: 0 on success.
 */

int custom_check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
