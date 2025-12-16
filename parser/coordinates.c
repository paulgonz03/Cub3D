#include "cube.h"

void find_coordinates(t_map *map_data, t_parse_flags *flags)
{
    int i;

    i = 0;
    while (map_data->map[i])
    {
        if (ft_strncmp(map_data->map[i], "NO", 2) == 0)
        {
            flags->pos_no = i;
            flags->no++;
        }
        if (ft_strncmp(map_data->map[i], "SO", 2) == 0)
        {
            flags->pos_so = i;
            flags->so++;
        }
        if (ft_strncmp(map_data->map[i], "WE", 2) == 0)
        {
            flags->pos_we = i;
            flags->we++;
        }
        if (ft_strncmp(map_data->map[i], "EA", 2) == 0)
        {
            flags->pos_ea = i;
            flags->ea++;
        }
        if (ft_strncmp(map_data->map[i], "F", 1) == 0)
        {
            flags->pos_f = i;
            flags->f++;
        }
        if (ft_strncmp(map_data->map[i], "C", 1) == 0)
        {
            flags->pos_c = i;
            flags->c++;
        }
        i++;
    }
}

int check_flags(t_parse_flags *flags)
{
    if (flags->c == 0 || flags->f == 0 || flags->no == 0 ||
        flags->so == 0 || flags->we == 0 || flags->ea == 0)
    {
        printf("Error: Missing coordinates\n");
        return (0);
    }
    if (flags->c > 1 || flags->f > 1 || flags->no > 1 || flags->so > 1 || flags->we > 1 || flags->ea > 1)
    {
        printf("Error: more coordinates\n");
        return (0);
    }
    return (1);
}

int fill_coordinates(t_map *map_data, t_parse_flags *flags)
{
    int i;

    i = 0;
    while (map_data->map && map_data->map[flags->pos_c][i] == 32)
        i++;
    map_data->files->c_file = ft_strdup(map_data->map[flags->pos_c]);
    i = 0;
    while (map_data->map && map_data->map[flags->pos_f][i] == 32)
        i++;
    map_data->files->f_file = ft_strdup(map_data->map[flags->pos_f]);
    i = 0;
    while (map_data->map && map_data->map[flags->pos_no][i] == 32)
        i++;
    map_data->files->no_file = ft_strdup(map_data->map[flags->pos_no]);
    i = 0;
    while (map_data->map && map_data->map[flags->pos_so][i] == 32)
        i++;
    map_data->files->so_file = ft_strdup(map_data->map[flags->pos_so]);
    i = 0;
    while (map_data->map && map_data->map[flags->pos_we][i] == 32)
        i++;
    map_data->files->we_file = ft_strdup(map_data->map[flags->pos_we]);
    i = 0;
    while (map_data->map && map_data->map[flags->pos_ea][i] == 32)
        i++;
    map_data->files->ea_file = ft_strdup(map_data->map[flags->pos_ea]);
    return (1);
}

int realloc_coordinates(t_map *map_data, t_parse_flags *flags)
{
    if (!realloc_map(map_data, flags->pos_no))
        return (0);
    if (!realloc_map(map_data, flags->pos_so))
        return (0);
    if (!realloc_map(map_data, flags->pos_we))
        return (0);
    if (!realloc_map(map_data, flags->pos_ea))
        return (0);
    if (!realloc_map(map_data, flags->pos_f))
        return (0);
    if (!realloc_map(map_data, flags->pos_c))
        return (0);
    return(1);
}

int coordinates_parser(t_map *map_data)
{
    t_parse_flags *flags;

    map_data->files = ft_calloc(1, sizeof(t_files));
    flags = ft_calloc(1, sizeof(t_parse_flags));
    find_coordinates(map_data, flags);
    if (!check_flags(flags))
        return (0);
    if (!fill_coordinates(map_data, flags))
        return (0);
    if (!realloc_coordinates(map_data, flags))
        return (0);
    printmap(map_data->map);
    return (1);
}
