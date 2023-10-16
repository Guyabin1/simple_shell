#include "shell.h"

/**
 * custom_alias - add, remove or else show aliases
 * @data: data program to struct.
 * @alias: printed name of alias
 * Return: zero if sucess.
 */
int custom_alias(data_of_program *data, char *alias)
{
	int i, j, length_alias;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		length_alias = custom_str_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (compare_string(data->alias_list[i], alias, length_alias)
				&&	data->alias_list[i][length_alias] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				custom_buffer_add(buffer, "'");
				custom_buffer_add(buffer, data->alias_list[i] + j + 1);
				custom_buffer_add(buffer, "'\n");
				custom_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * _getalias - add, remove or view aliases
 * @data: data program to be struct
 * @name: name of t.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *_getalias(data_of_program *data, char *name)
{
	int i, length_alias;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	length_alias = custom_str_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{
		if (compare_string(name, data->alias_list[i], length_alias) &&
			data->alias_list[i][length_alias] == '=')
		{
			return (data->alias_list[i] + length_alias + 1);
		}
	}
	return (NULL);

}

/**
 * alias_set - add, or get away with alias
 * @alias_string: form of alias set.
 * @data: struct data.
 * Return: zero if sucess.
 */
int alias_set(char *alias_string, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			temp = _getalias(data, alias_string + i + 1);
			break;
		}

	for (j = 0; data->alias_list[j]; j++)
		if (compare_string(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{
			free(data->alias_list[j]);
			break;
		}

	if (temp)
	{
		custom_buffer_add(buffer, "=");
		custom_buffer_add(buffer, temp);
		data->alias_list[j] = str_copy(buffer);
	}
	else
		data->alias_list[j] = str_copy(alias_string);
	return (0);
}
