#include "cube.h"

int check_order(t_parse_flags *flags)
{
    if (flags->pos_no > flags->pos_c || flags->pos_no > flags->pos_f || flags->pos_no > flags->pos_ea || flags->pos_no > flags->we || flags->pos_no > flags->pos_so)
        return (0);
    if (flags->pos_so > flags->pos_c || flags->pos_so > flags->pos_f || flags->pos_so > flags->pos_ea || flags->pos_so > flags->pos_we)
        return (0);
    if (flags->pos_we > flags->pos_c || flags->pos_we > flags->pos_f || flags->pos_we > flags->pos_ea)
        return (0);
    if (flags->pos_ea > flags->pos_c || flags->pos_ea > flags->pos_f)
        return (0);
    if (flags->pos_f > flags->pos_c)
        return (0);
    return (1);
}

int realloc_coordinates(t_map *map_data, t_parse_flags *flags)
{
    if (!realloc_map(map_data, flags->pos_no))
        return (0);
    find_coordinates(map_data, flags);
    if (!realloc_map(map_data, flags->pos_so))
        return (0);
    find_coordinates(map_data, flags);
    if (!realloc_map(map_data, flags->pos_we))
        return (0);
    find_coordinates(map_data, flags);
    if (!realloc_map(map_data, flags->pos_ea))
        return (0);
    find_coordinates(map_data, flags);
    if (!realloc_map(map_data, flags->pos_f))
        return (0);
    find_coordinates(map_data, flags);
    if (!realloc_map(map_data, flags->pos_c))
        return (0);
    return (1);
}
