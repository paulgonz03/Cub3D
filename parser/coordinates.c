#include "cube.h"

int	process_line(t_realloc *data, t_map *map_data, int pos)
{
	if (data->j == pos)
	{
		if (map_data->map[data->j + 1][0] == '\n')
		{
			data->j++;
			data->newline++;
		}
		data->j++;
		return (1);
	}
	if (data->newline > 1)
		return (0);
	data->new_map[data->i] = ft_strdup(map_data->map[data->j]);
	data->i++;
	data->j++;
	return (2);
}

int	realloc_map(t_map *map_data, int pos)
{
	t_realloc	*data;
	int			result;

	data = ft_calloc(1, sizeof(t_realloc));
	while (map_data->map[data->lines])
		data->lines++;
	data->new_map = ft_calloc(data->lines + 1, sizeof(char *));
	if (!data->new_map)
		return (free(data), 0);
	while (map_data->map[data->j])
	{
		result = process_line(data, map_data, pos);
		if (result == 0)
			return (free(data->new_map), free(data),
				printf("Error: more newlines\n"), 0);
		if (result == 1)
			continue ;
	}
	data->new_map[data->i] = NULL;
	ft_free_free(map_data->map);
	map_data->map = data->new_map;
	map_data->lines = data->i;
	free(data);
	return (1);
}

int	aux_coordinates_parser(t_map *map_data, char *coords[6], int j, int i)
{
	if (j == 0)
		map_data->files->no_file = ft_strtrim(map_data->map[i]
				+ ft_strlen(coords[j]), " \t\n");
	else if (j == 1)
		map_data->files->so_file = ft_strtrim(map_data->map[i]
				+ ft_strlen(coords[j]), " \t\n");
	else if (j == 2)
		map_data->files->we_file = ft_strtrim(map_data->map[i]
				+ ft_strlen(coords[j]), " \t\n");
	else if (j == 3)
		map_data->files->ea_file = ft_strtrim(map_data->map[i]
				+ ft_strlen(coords[j]), " \t\n");
	else if (j == 4)
		map_data->files->f_file = ft_strtrim(map_data->map[i]
				+ ft_strlen(coords[j]), " \t\n");
	else if (j == 5)
		map_data->files->c_file = ft_strtrim(map_data->map[i]
				+ ft_strlen(coords[j]), " \t\n");
	if (!realloc_map(map_data, i))
		return (0);
	return (1);
}

int	coordinates_parser(t_map *map_data, char **coords)
{
	int	i;
	int	j;

	coords[0] = "NO";
	coords[1] = "SO";
	coords[2] = "WE";
	coords[3] = "EA";
	coords[4] = "F";
	coords[5] = "C";
	i = 0;
	j = -1;
	while (map_data->map[i] && ++j < 6)
	{
		if (map_data->map[i][0] == '\n')
			i++;
		else if (ft_strncmp(map_data->map[i], coords[j],
				ft_strlen(coords[j])) == 0)
		{
			if (!aux_coordinates_parser(map_data, coords, j, i))
				return (0);
		}
		else
			return (0);
	}
	return (j == 6);
}
