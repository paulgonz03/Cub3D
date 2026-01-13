#include "cube.h"

void ft_free_free(char **temp)
{
    int j;

    j = -1;
    while (temp[++j])
        free(temp[j]);
    free(temp);
}


