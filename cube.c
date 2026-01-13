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
    t_map map_data;
    t_files files;

    if (argc != 2)
    {
        printf("Error: not enough arguments\n");
        return (0);
    }
    ft_bzero(&map_data, sizeof(map_data));
    ft_bzero(&files, sizeof(files));
    map_data.files = &files;
    if (!name_map_parser(argv))
        return (error(&map_data, "Error: name map file"));
    if (!get_map(argv, &map_data))
        return (error(&map_data, "Error get_map\n"));
    if (!parser(&map_data))
        return (error(&map_data, "Error: Invalid map"));
    if (!raycast(&map_data))
    {
        free_mapdata(&map_data);
        return (0);
    }
}
