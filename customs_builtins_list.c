#include "shell.h"

/**
 * _builtins_list - after search for the match execute the associatewd file
 * @data: struct.
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int _builtins_list(data_of_program *data)
{
	int iterator;
	builtins options[] = {
		{"exit", customs_builtin_exit},
		{"help", custom_builtin_support},
		{"cd", _builtin_command},
		{"alias", custom_builtin_alias},
		{"env", custom_buitin_environ},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unpaired_environ},
		{NULL, NULL}
	};

	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
		if (compare_string(options[iterator].builtin, data->command_name, 0))
		{
			return (options[iterator].function(data));
		}
	}
	return (-1);
}
