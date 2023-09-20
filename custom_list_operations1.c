#include "shell.h"

/**
 * list_length - Computes the length of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t list_length(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * list_to_string_array - Converts a linked list of strings to a string array.
 * @head: Pointer to the first node.
 *
 * Return: An array of strings.
 */
char **list_to_string_array(list_t *head)
{
	list_t *node = head;
	size_t list_size = list_length(head);
	char **str_array;
	char *str;

	if (!head || !list_size)
		return (NULL);

	str_array = malloc(sizeof(char *) * (list_size + 1));
	if (!str_array)
		return (NULL);

	for (size_t i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < i; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		str_array[i] = str;
	}

	str_array[list_size] = NULL;
	return (str_array);
}

/**
 * print_list_elements - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_list_elements(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * find_node_with_prefix - Returns the node whose string starts with a prefix.
 * @node: Pointer to the list head.
 * @prefix: The prefix string to match.
 * @c: The character following the prefix to match.
 *
 * Return: The matching node or NULL.
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}

	return (NULL);
}

/**
 * get_node_index - Retrieves the index of a node.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: The index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}

	return (-1);
}
