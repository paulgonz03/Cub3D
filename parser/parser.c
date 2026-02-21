#include "cube.h"

int parser(t_map *map_data)
{
    if (!coordinates_parser(map_data))
        return (0);
    if (!char_not_allow(map_data->map))
        return (0);
    if (!flood_fill(map_data))
        return (0);
    sky_floor(map_data);
    return (1);
}