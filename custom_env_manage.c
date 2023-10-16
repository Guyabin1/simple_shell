#include "shell.h"

/**
* custom_env_get_key - gets the value of an environment variable
* @key: the environment variable of interest
* @data: struct.
* Return: a pointer to the value of the variable or NULL
*/
char *custom_env_get_key(char *key, data_of_program *data)
{
int i, key_length = 0;

if (key == NULL || data->env == NULL)
return (NULL);


key_length = custom_str_length(key);

for (i = 0; data->env[i]; i++)
{
if (compare_string(key, data->env[i], key_length) &&
data->env[i][key_length] == '=')
{
return (data->env[i] + key_length + 1);
}
}

return (NULL);
}

/**
* custom_env_set_key - the value of environment is overwritten
* or create it if does not exist.
* @key: name of the variable to set
* @value: new value
* @data: struct.
* Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
*/

int custom_env_set_key(char *key, char *value, data_of_program *data)
{
int i, key_length = 0, is_new_key = 1;

if (key == NULL || value == NULL || data->env == NULL)
return (1);


key_length = custom_str_length(key);

for (i = 0; data->env[i]; i++)
{
if (compare_string(key, data->env[i], key_length) &&
data->env[i][key_length] == '=')
{
is_new_key = 0;

free(data->env[i]);
break;
}
}

data->env[i] = string_combined(str_copy(key), "=");
data->env[i] = string_combined(data->env[i], value);

if (is_new_key)
{

data->env[i + 1] = NULL;
}
return (0);
}

/**
* custom_env_remove_key - remove a key from the environment
* @key: the key to remove
* @data: the sruct.
* Return: 1 if the key was removed, 0 if the key does not exist;
*/
int custom_env_remove_key(char *key, data_of_program *data)
{
int i, key_length = 0;


if (key == NULL || data->env == NULL)
return (0);


key_length = custom_str_length(key);

for (i = 0; data->env[i]; i++)
{
if (compare_string(key, data->env[i], key_length) &&
data->env[i][key_length] == '=')
{
free(data->env[i]);


i++;
for (; data->env[i]; i++)
{
data->env[i - 1] = data->env[i];
}

data->env[i - 1] = NULL;
return (1);
}
}
return (0);
}


/**
* custom_env_print - prints the current environment
* @data: struct.
* Return: null
*/
void custom_env_print(data_of_program *data)
{
int j;

for (j = 0; data->env[j]; j++)
{
custom_print(data->env[j]);
custom_print("\n");
}
}
