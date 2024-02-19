skiplist_t *linear_skip(skiplist_t *list, int value)
{
    skiplist_t *express, *prev;

    if (list == NULL)
        return NULL;

    express = list->express;
    prev = list;

    while (express && express->n < value)
    {
        printf("Value checked at index [%lu] = [%d]\n",
               express->index, express->n);
        prev = express;
        express = express->express;
    }

    if (express == NULL)
    {
        express = prev;
        while (express->next)
            express = express->next;
    }

    printf("Value found between indexes [%lu] and [%lu]\n",
           prev->index, express->index);

    while (prev && prev->n < value)
    {
        printf("Value checked at index [%lu] = [%d]\n",
               prev->index, prev->n);
        prev = prev->next;
    }

    if (prev == NULL || prev->n != value)
        return NULL;

    printf("Value checked at index [%lu] = [%d]\n",
           prev->index, prev->n);

    return prev;
}
