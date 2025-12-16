#include "cube.h"

void ft_free_free(char **temp)
{
    int j;

    j = -1;
    while(temp[++j])
        free(temp[j]);
    free(temp);
}

int realloc_map(t_map *map_data, int pos)
{
    char **new_map;
    int j; 
    int i;
    int lines; 

    j = 0;
    i = 0;
    lines = 0;
    while (map_data->map[lines])
        lines++;
    new_map = ft_calloc(lines, sizeof(char *));
    if (!new_map)
        return(0);
    while (map_data->map[j])
    {
        if (j == pos)
        {
            j++;
            continue;
        }
        if (map_data->map[j])
            new_map[i++] = ft_strdup(map_data->map[j]);
        j++;
    }
    new_map[i] = NULL;
    ft_free_free(map_data->map);
    map_data->map = new_map;
    return(1);
}
