#include "cube.h"

int char_not_allow(char **map)
{
    int i;
    int j;

    j = 0;
    while (map[j][0] == '\n')
        j++;
    while (map[j])
    {
        i = -1;
        while (map[j][++i])
        {
            if (!(map[j][i] == '1' || map[j][i] == '0' || map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'O' || map[j][i] == 'E' || map[j][i] == '\n' || map[j][i] == 32))
            {
                printf("Error: char invalid in map\n");
                return (0);
            }
        }
        j++;
    }
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
    if (!char_not_allow(map_data->map))
        return (0);
    if (!flood_fill(map_data))
        return (0);
    return (1);
}