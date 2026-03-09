#include "cube.h"
#include "minilibx-linux/mlx.h"

// verifica coordenadas y devuelve el tipo de casilla
static int	get_map_tile(t_map *map_data, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0) // comprueba los limites
		return (-1);
	if (map_y >= map_data->y_limit) // si es invalido
		return (-1);
	if (!map_data->map[map_y]) // si es invalido
		return (-1);
	if (map_x >= (int)ft_strlen(map_data->map[map_y]))
		return (-1);
	return (map_data->map[map_y][map_x]); // devuelve el caracter
}

// dibuja la flecha del personaje
static void	draw_player(t_mlx *mlx_data, int cx, int cy, float angle)
{
	draw_circle(mlx_data, cx, cy);
	draw_direction(mlx_data, cx, cy, angle);
}

// obtiene la imagen segun el tipo de tile
static void	*get_tile_img(t_minimap *mini_map, int tile)
{
	if (tile == '1')
		return (mini_map->wall_img);
	else if (tile == 'T')
		return (mini_map->fire_img);
	else if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'E'
		|| tile == 'W')
		return (mini_map->floor_img);
	else
		return (mini_map->void_img);
}

// renderiza los tiles del minimapa
static void	render_tiles(t_map *map_data, t_minimap *mini_map, float off[2])
{
	t_mlx	*mlx;
	int		x;
	int		y;
	int		tile;

	mlx = map_data->mlx_data;
	y = -1;
	while (++y <= MINIMAP_SIZE)
	{
		x = -1;
		while (++x <= MINIMAP_SIZE)
		{
			tile = get_map_tile(map_data, (int)map_data->x_plyr + x
					- MINIMAP_SIZE / 2, (int)map_data->y_plyr + y - MINIMAP_SIZE
					/ 2);
			mlx_put_image_to_window(mlx->mlx, mlx->win, get_tile_img(mini_map,
					tile), x * TILE_SIZE + MINIMAP_OFFSET - (int)(off[0]
					* TILE_SIZE), y * TILE_SIZE + MINIMAP_OFFSET - (int)(off[1]
					* TILE_SIZE));
		}
	}
}

int	mini_map(t_map *map_data, t_minimap *mini_map)
{
	t_mlx		*mlx_data;
	static int	loaded = 0;
	float		off[2];

	mlx_data = map_data->mlx_data;
	if (!loaded && !load_minimap_textures(map_data, mini_map))
		return (0);
	loaded = 1;
	off[0] = map_data->x_plyr - (int)map_data->x_plyr;
	off[1] = map_data->y_plyr - (int)map_data->y_plyr;
	render_tiles(map_data, mini_map, off);
	draw_player(mlx_data, MINIMAP_OFFSET + (MINIMAP_SIZE * TILE_SIZE) / 2,
		MINIMAP_OFFSET + (MINIMAP_SIZE * TILE_SIZE) / 2, mlx_data->plyr_angle);
	return (1);
}
