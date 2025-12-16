#include "cube.h"

int name_map_parser(char **argv)
{
    int len;

    len = ft_strlen(argv[1]);
    if (len < 5)
        return (0);
    if (!(argv[1][len - 1] == 'b' && argv[1][len - 2] == 'u' && argv[1][len - 3] == 'c' && argv[1][len - 4] == '.'))
        return (0);
    return(1);

}

int parser(t_map *map_data)
{
    if (!coordinates_parser(map_data))
        return (0);
    return(1);
}