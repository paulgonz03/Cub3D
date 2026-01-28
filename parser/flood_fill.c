#include "cube.h"

char **copy_map(t_map *map_data)
{
    int j;
    int i;
    char **temp;

    j = 0;
    i = 0;
    while (map_data->map[j])
        j++;
    temp = ft_calloc(j + 1, sizeof(char *));
    j = 0;
    while (map_data->map[j])
    {
        temp[i] = ft_strdup(map_data->map[j]);
        i++;
        j++;
    }
    temp[i] = '\0';
    return (temp);
}

void find_player(t_map *map_data)
{
    int y;
    int x;
    
    y = 0;
    while (map_data->map[y][0] == '\n')
        y++;
    while (map_data->map[y])
    {
        x = 0;
        while (map_data->map[y][x])
        {
            if (map_data->map[y][x] == 'N' || map_data->map[y][x] == 'S' || map_data->map[y][x] == 'E' || map_data->map[y][x] == 'W')
            {
                map_data->view_player = map_data->map[y][x];
                map_data->type = map_data->map[y][x];
                map_data->x_plyr = (float)x + 0.5f;
                map_data->y_plyr = (float)y + 0.5f;
                return;
            }
            x++;
        }
        y++;
    }
}

void limits_map(t_map *map_data)
{
    int j;
    int len;

    len = 0;
    j = 0;
    map_data->x_limit = 0;
    map_data->y_limit = 0;
    while (map_data->map[map_data->y_limit])
        map_data->y_limit++;
    len = ft_strlen(map_data->map[j]);
    while (map_data->map[j] && ft_strlen(map_data->map[j]) > len)
    {
        len = ft_strlen(map_data->map[j]);
        j++;
    }
    map_data->x_limit = len;
}

int aux_flood_fill(t_map *map_data, int x, int y, char **map)
{
    if (y < 0 || y >= map_data->y_limit || x < 0)
        return (0);
    if (!map[y])
        return (0);
    if (x >= (int)ft_strlen(map[y]) || map[y][x] == ' ')
        return (0);
    if (map[y][x] == 'x' || map[y][x] == '1')
        return (1);
    map[y][x] = 'x';
    if (!aux_flood_fill(map_data, x, y + 1, map))
        return (0);
    if (!aux_flood_fill(map_data, x, y - 1, map))
        return (0);
    if (!aux_flood_fill(map_data, x + 1, y, map))
        return (0);
    if (!aux_flood_fill(map_data, x - 1, y, map))
        return (0);
    return (1);
}

int flood_fill(t_map *map_data)
{
    char **temp;

    temp = copy_map(map_data);
    find_player(map_data);
    limits_map(map_data);
    if (!aux_flood_fill(map_data, (int)map_data->x_plyr, (int)map_data->y_plyr, temp))
    {
        ft_free_free(temp);
        printf("Error: open map\n");
        return (0);
    }
    ft_free_free(temp);
    return (1);
}