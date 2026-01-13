#include "cube.h"

int realloc_map(t_map *map_data, int pos)
{
    char **new_map;
    int j;
    int i;
    int lines;
    int newline;

    j = 0;
    i = 0;
    lines = 0;
    newline = 0;
    while (map_data->map[lines])
        lines++;
    new_map = ft_calloc(lines, sizeof(char *));
    if (!new_map)
        return (0);
    while (map_data->map[j])
    {
        if (j == pos)
        {
            if (map_data->map[j+1][0] == '\n')
            {
                j++;
                newline++;
            }
            j++;
            continue;
        }
        if (newline > 1)
        {
            printf("Error: more newlines\n");
            return (0);
        }
        if (map_data->map[j])
            new_map[i++] = ft_strdup(map_data->map[j]);
        j++;
    }
    new_map[i] = NULL;
    ft_free_free(map_data->map);
    map_data->map = new_map;
    return (1);
}

int coordinates_parser(t_map *map_data)
{
    int     i;
    int     j;
    char    *coords[6];

    coords[0] = "NO";
    coords[1] = "SO";
    coords[2] = "WE";
    coords[3] = "EA";
    coords[4] = "F";
    coords[5] = "C";
    i = 0;
    j = 0;
    while (map_data->map[i] && j < 6)
    {
        if (map_data->map[i][0] == '\n')
            i++;
        else if (ft_strncmp(map_data->map[i], coords[j], ft_strlen(coords[j])) == 0)
        {
            if (j == 0)
                map_data->files->no_file = ft_strtrim(map_data->map[i] + ft_strlen(coords[j]), " \t\n");
            else if (j == 1)
                map_data->files->so_file = ft_strtrim(map_data->map[i] + ft_strlen(coords[j]), " \t\n");
            else if (j == 2)
                map_data->files->we_file = ft_strtrim(map_data->map[i] + ft_strlen(coords[j]), " \t\n");
            else if (j == 3)
                map_data->files->ea_file = ft_strtrim(map_data->map[i] + ft_strlen(coords[j]), " \t\n");
            else if (j == 4)
                map_data->files->f_file = ft_strtrim(map_data->map[i] + ft_strlen(coords[j]), " \t\n");
            else if (j == 5)
                map_data->files->c_file = ft_strtrim(map_data->map[i] + ft_strlen(coords[j]), " \t\n");
            if (!realloc_map(map_data, i))
                return (0);
            j++;
        }
        else
            return (0);
    }
    return (j == 6);
}
