#include "cube.h"

int aux_get_map(char **argv, t_map *data_map)
{
    int fd;
    int j;

    j = 0;
    data_map->map = ft_calloc(data_map->lines, sizeof(char *));
    if (!data_map->map)
        return (0);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        free(data_map->map);
        return (0);
    }
    data_map->map[j] = get_next_line(fd);
    while (data_map->map[j++] != NULL)
    {

        data_map->map[j] = get_next_line(fd);
        if (data_map->map[j] == NULL) // llegar al final del mapa
            break;
    }
    return(1);
}

int get_map(char **argv, t_map *map_data)
{
    int fd;

    map_data->lines = 0;
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (0);
    map_data->temp = get_next_line(fd);
    while (map_data->temp != NULL)
    {
        free(map_data->temp);
        map_data->temp = get_next_line(fd);
        map_data->lines++;
    }
    close(fd);
    if (!aux_get_map(argv, map_data))
        return (0);
    return (1);
}