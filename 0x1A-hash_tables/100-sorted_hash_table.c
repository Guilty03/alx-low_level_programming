#include "hash_tables.h"

shash_table_t *shash_table_create(unsigned long int size);
int shash_table_set(shash_table_t *HT, const char *key, const char *value);
char *shash_table_get(const shash_table_t *HT, const char *key);
void shash_table_print(const shash_table_t *HT);
void shash_table_print_rev(const shash_table_t *HT);
void shash_table_delete(shash_table_t *HT);

/**
 * shash_table_create - Creates a sorted hash table.
 * @size: The size of new sorted hash table.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new sorted hash table.
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *HT;
	unsigned long int i;

	HT = malloc(sizeof(shash_table_t));
	if (HT == NULL)
		return (NULL);

	HT->size = size;
	HT->array = malloc(sizeof(shash_node_t *) * size);
	if (HT->array == NULL)
		return (NULL);
	for (i = 0; i < size; i++)
		HT->array[i] = NULL;
	HT->shead = NULL;
	HT->stail = NULL;

	return (HT);
}

/**
 * shash_table_set - Adds an element to a sorted hash table.
 * @HT: A pointer to the sorted hash table.
 * @key: The key to add - cannot be an empty string.
 * @value: The value associated with key.
 *
 * Return: Upon failure - 0.
 *         Otherwise - 1.
 */
int shash_table_set(shash_table_t *HT, const char *key, const char *value)
{
	shash_node_t *new, *temp;
	char *value_copy;
	unsigned long int index;

	if (HT == NULL || key == NULL || value ==NULL || *key == '\0' )
		return (0);

	value_copy = strdup(value);
	if (value_copy == NULL)
		return (0);

	index = key_index((const unsigned char *)key, HT->size);
	temp = HT->shead;
	while (temp)
	{
		if (strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = value_copy;
			return (1);
		}
		temp = temp->snext;
	}

	new = malloc(sizeof(shash_node_t));
	if (new == NULL)
	{
		free(value_copy);
		return (0);
	}
	new->key = strdup(key);
	if (new->key == NULL)
	{
		free(value_copy);
		free(new);
		return (0);
	}
	new->value = value_copy;
	new->next = HT->array[index];
	HT->array[index] = new;

	if (HT->shead == NULL)
	{
		new->sprev = NULL;
		new->snext = NULL;
		HT->shead = new;
		HT->stail = new;
	}
	else if (strcmp(HT->shead->key, key) > 0)
	{
		new->sprev = NULL;
		new->snext = HT->shead;
		HT->shead->sprev = new;
		HT->shead = new;
	}
	else
	{
		temp = HT->shead;
		while (temp->snext != NULL && strcmp(temp->snext->key, key) < 0)
			temp = temp->snext;
		new->sprev = temp;
		new->snext = temp->snext;
		if (temp->snext == NULL)
			HT->stail = new;
		else
			temp->snext->sprev = new;
		temp->snext = new;
	}

	return (1);
}

/**
 * shash_table_get - Retrieve the value associated with
 *                   a key in a sorted hash table.
 * @HT: A pointer to the sorted hash table.
 * @key: The key to get the value of.
 *
 * Return: If the key cannot be matched - NULL.
 *         Otherwise - the value associated with key in HT.
 */
char *shash_table_get(const shash_table_t *HT, const char *key)
{
	shash_node_t *node;
	unsigned long int index;

	if (HT == NULL || key == NULL || *key == '\0')
		return (NULL);

	index = key_index((const unsigned char *)key, HT->size);
	if (index >= HT->size)
		return (NULL);

	node = HT->shead;
	while (node != NULL && strcmp(node->key, key) != 0)
		node = node->snext;

	return ((node == NULL) ? NULL : node->value);
}

/**
 * shash_table_print - Prints a sorted hash table in order.
 * @HT: A pointer to the sorted hash table.
 */
void shash_table_print(const shash_table_t *HT)
{
	shash_node_t *node;

	if (HT == NULL)
		return;

	node = HT->shead;
	printf("{");
	while (node != NULL)
	{
		printf("'%s': '%s'", node->key, node->value);
		node = node->snext;
		if (node != NULL)
			printf(", ");
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - Prints a sorted hash table in reverse order.
 * @HT: A pointer to the sorted hash table to print.
 */
void shash_table_print_rev(const shash_table_t *HT)
{
	shash_node_t *node;

	if (HT == NULL)
		return;

	node = HT->stail;
	printf("{");
	while (node != NULL)
	{
		printf("'%s': '%s'", node->key, node->value);
		node = node->sprev;
		if (node != NULL)
			printf(", ");
	}
	printf("}\n");
}

/**
 * shash_table_delete - Deletes a sorted hash table.
 * @HT: A pointer to the sorted hash table.
 */
void shash_table_delete(shash_table_t *HT)
{
	shash_table_t *head = HT;
	shash_node_t *node, *temp;

	if (HT == NULL)
		return;

	node = HT->shead;
	while (node)
	{
		temp = node->snext;
		free(node->key);
		free(node->value);
		free(node);
		node = temp;
	}

	free(head->array);
	free(head);
}

