#include "cube.h"

int	parser(t_map *map_data)
{
	char	*coords[6];

	if (!char_parser(map_data->map, '\t'))
		return (0);
	if (!coordinates_parser(map_data, coords))
		return (0);
	if (!char_not_allow(map_data->map))
		return (0);
	if (!flood_fill(map_data))
		return (0);
	if (!sky_floor(map_data))
		return (0);
	return (1);
}
