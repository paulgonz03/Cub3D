#include "cube.h"

void printmap(char **map)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (map[y])
    {
        while (map[y][x])
        {
            printf("%c", map[y][x]);
            x++;
        }
        x = 0;
        y++;
    }
    printf("\n");
    return;
}

int main(int argc, char **argv)
{
    t_map *map_data;

    if (argc != 2)
    {
        printf("Error: not enough arguments\n");
        return (0);
    }
    map_data = ft_calloc(1, sizeof(t_map));
    if (!map_data)
    {
        printf("Error: failed create struct\n");
        return (0);
    }
    if (!name_map_parser(argv))
        return (error(map_data, "Error: name map file"));
    if (!get_map(argv, map_data))
        return (error(map_data, "Error get_map\n"));
    if (!parser(map_data))
    {
        free_mapdata(map_data);
        return (0);
    }
    if (!raycast(map_data))
    {
        free_mapdata(map_data);
        return (0);
    }
}
