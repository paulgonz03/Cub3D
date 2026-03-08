#include "cube.h"

void	ft_free_free(char **temp)
{
	int	j;

	j = -1;
	while (temp[++j])
		free(temp[j]);
	free(temp);
}

int	char_not_allow(char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j] && map[j][0] == '\n')
		j++;
	if (!map[j])
		return (printf("Error: no map found\n"), 0);
	while (map[j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (!(map[j][i] == '1' || map[j][i] == '0' || map[j][i] == 'N'
					|| map[j][i] == 'S' || map[j][i] == 'W' || map[j][i] == 'E'|| map[j][i] == 'T'
					|| map[j][i] == '\n' || map[j][i] == 32))
			{
				printf("Error: char invalid in map\n");
				return (0);
			}
		}
		j++;
	}
	return (1);
}

int	name_map_parser(char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (len < 5)
		return (0);
	if (!(argv[1][len - 1] == 'b' && argv[1][len - 2] == 'u' && argv[1][len
			- 3] == 'c' && argv[1][len - 4] == '.'))
		return (0);
	return (1);
}

static int	is_valid_rgb_value(char *s)
{
    int	i;
    int	val;

    i = 0;
    while (s[i] == ' ' || s[i] == '\t')
        i++;
    if (!s[i])
        return (0);
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return (0);
        i++;
    }
    val = ft_atoi(s);
    return (val >= 0 && val <= 255);
}

int	validate_rgb_split(char **rgb)
{
    int	i;

    if (!rgb)
        return (0);
    i = 0;
    while (rgb[i])
        i++;
    if (i != 3)
        return (0);
    i = -1;
    while (++i < 3)
    {
        if (!rgb[i] || !is_valid_rgb_value(rgb[i]))
            return (0);
    }
    return (1);
}

int	sky_floor(t_map *map_data)
{
    char	**floor;
    char	**sky;

    if (!map_data->files->f_file || !map_data->files->c_file)
        return (0);
    floor = ft_split(map_data->files->f_file, ',');
    sky = ft_split(map_data->files->c_file, ',');
    if (!validate_rgb_split(floor) || !validate_rgb_split(sky))
    {
        if (floor)
            ft_free_free(floor);
        if (sky)
            ft_free_free(sky);
        return (0);
    }
    map_data->files->c_col_r = ft_atoi(sky[0]);
    map_data->files->c_col_g = ft_atoi(sky[1]);
    map_data->files->c_col_b = ft_atoi(sky[2]);
    map_data->files->f_col_r = ft_atoi(floor[0]);
    map_data->files->f_col_g = ft_atoi(floor[1]);
    map_data->files->f_col_b = ft_atoi(floor[2]);
    ft_free_free(floor);
    ft_free_free(sky);
    return (1);
}


int tab_parser(char **map) 
{
	int i;
	int j;

	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
			if (map[j][i] == '\t')
				return(0);
	}
	return(1);
}
