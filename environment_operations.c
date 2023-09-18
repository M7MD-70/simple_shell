#include "shell.h"

/**
 * retrieve_environment - returns a copy of the environment strings
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Array of strings representing the environment.
 */
char **retrieve_environment(info_t *info)
{
	if (!info->environment || info->environment_changed)
	{
		info->environment = convert_list_to_strings(info->env_list);
		info->environment_changed = 0;
	}

	return (info->environment);
}

/**
 * unset_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: The name of the environment variable to unset.
 *
 * Return: 1 if variable was successfully unset, 0 otherwise.
 */
int unset_environment_variable(info_t *info, char *variable)
{
	list_t *node = info->env_list;
	size_t index = 0;
	char *property;

	if (!node || !variable)
		return (0);

	while (node)
	{
		property = starts_with(node->str, variable);
		if (property && *property == '=')
		{
			info->environment_changed = delete_node_at_index(&(info->env_list), index);
			index = 0;
			node = info->env_list;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->environment_changed);
}

/**
 * set_environment_variable - Initialize a new environment variable
 *                            or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: The name of the environment variable.
 * @value: The value to assign to the environment variable.
 *
 * Return: Always 0.
 */
int set_environment_variable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *property;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);

	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);

	node = info->env_list;
	while (node)
	{
		property = starts_with(node->str, variable);
		if (property && *property == '=')
		{
			free(node->str);
			node->str = buffer;
			info->environment_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env_list), buffer, 0);
	free(buffer);
	info->environment_changed = 1;
	return (0);
}
