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
    t_map *map;

    map = ft_calloc(1, sizeof(t_map));
    if (argc != 2)
        return (printf("Error arguments\n"));
    if (!name_map_parser(argv))
        return (printf("Error name map\n"));
    if (!get_map(argv, map))
        return (printf("Error get_map\n"));
    if (!parser(map))
        return(0);
}
