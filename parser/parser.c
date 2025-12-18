#include "cube.h"

void find_player(t_map *map_data)
{
    map_data->y = 0;
    while (map_data->map[map_data->y][0] == '\n')
        map_data->y++;
    while (map_data->map[map_data->y])
    {
        map_data->x = 0;
        while (map_data->map[map_data->y][map_data->x])
        {
            if (map_data->map[map_data->y][map_data->x] == 'N' || map_data->map[map_data->y][map_data->x] == 'S' || map_data->map[map_data->y][map_data->x] == 'E' || map_data->map[map_data->y][map_data->x] == 'W')
            {
                map_data->type = map_data->map[map_data->y][map_data->x];
                return ;
            }
            map_data->x++;
        }
        map_data->y++;
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

void aux_flood_fill(t_map *map_data, int x, int y)
{   
    if (x > map_data->x_limit || y > map_data->y_limit)
    {
        printf("Error: open walls\n");
        exit(1);
    }
    if (map_data->map[y][x] == 'x' || map_data->map[y][x] == '1')
        return ;
    map_data->map[y][x] = 'x';
    aux_flood_fill(map_data, x, y+1);
    aux_flood_fill(map_data, x, y-1);
    aux_flood_fill(map_data, x+1, y);
    aux_flood_fill(map_data, x-1, y);
}

int flood_fill(t_map *map_data)
{
    find_player(map_data);
    limits_map(map_data);
    printf("x: %d\n", map_data->x);
    printf("x_limmit: %d\n", map_data->x_limit);
    printf("y: %d\n", map_data->y);
    printf("y_limit: %d\n", map_data->y_limit);
    aux_flood_fill(map_data, map_data->x, map_data->y);
    return (1);
}

int name_map_parser(char **argv)
{
    int len;

    len = ft_strlen(argv[1]);
    if (len < 5)
        return (0);
    if (!(argv[1][len - 1] == 'b' && argv[1][len - 2] == 'u' && argv[1][len - 3] == 'c' && argv[1][len - 4] == '.'))
        return (0);
    return (1);
}

int parser(t_map *map_data)
{
    if (!coordinates_parser(map_data))
        return (0);
    if (!flood_fill(map_data))
        return (0);
    return (1);
}