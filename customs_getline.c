#include "shell.h"

/**
* get_line - one line must be read from prompt.
* @data: struct.
*
* Return: reading counting bytes.
*/
int get_line(data_of_program *data)
{
char buff[BUFFER_SIZE] = {'\0'};
static char *array_commands[10] = {NULL};
static char array_operators[10] = {'\0'};
ssize_t bytes_read, i = 0;

if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
(array_operators[0] == '|' && errno == 0))
{
for (i = 0; array_commands[i]; i++)
{
free(array_commands[i]);
array_commands[i] = NULL;
}
bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
if (bytes_read == 0)
return (-1);

i = 0;
do {
array_commands[i] = str_copy(custom_strtok(i ? NULL : buff, "\n;"));

i = _customcheck_logic_ops(array_commands, i, array_operators);
} while (array_commands[i++]);
}


data->input_line = array_commands[0];
for (i = 0; array_commands[i]; i++)
{
array_commands[i] = array_commands[i + 1];
array_operators[i] = array_operators[i + 1];
}

return (custom_str_length(data->input_line));
}


/**
* _customcheck_logic_ops - checks and split for &&
* @array_commands: array of the commands.
* @i: index in the array_commands.
* @array_operators: the logical operators for each last command
*Return: index of the previous command
*/
int _customcheck_logic_ops(char *array_commands[], int i, char array_operators[])
{
char *temp = NULL;
int j;

for (j = 0; array_commands[i] != NULL  && array_commands[i][j]; j++)
{
if (array_commands[i][j] == '&' && array_commands[i][j + 1] == '&')
{
temp = array_commands[i];
array_commands[i][j] = '\0';
array_commands[i] = str_copy(array_commands[i]);
array_commands[i + 1] = str_copy(temp + j + 2);
i++;
array_operators[i] = '&';
free(temp);
j = 0;
}
if (array_commands[i][j] == '|' && array_commands[i][j + 1] == '|')
{
temp = array_commands[i];
array_commands[i][j] = '\0';
array_commands[i] = str_copy(array_commands[i]);
array_commands[i + 1] = str_copy(temp + j + 2);
i++;
array_operators[i] = '|';
free(temp);
j = 0;
}
}
return (i);
}
