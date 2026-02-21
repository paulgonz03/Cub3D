#include "cube.h"
#include "minilibx-linux/mlx.h"

// Check if map coordinates are valid and return the tile type
static int	get_map_tile(t_map *map_data, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0)
		return (-1);
	if (map_y >= map_data->y_limit)
		return (-1);
	if (!map_data->map[map_y])
		return (-1);
	if (map_x >= (int)ft_strlen(map_data->map[map_y]))
		return (-1);
	return (map_data->map[map_y][map_x]);
}

// Create a colored tile image as fallback
static void	*create_tile_img(t_mlx *mlx_data, int size, int color)
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		x;
	int		y;

	img = mlx_new_image(mlx_data->mlx, size, size);
	if (!img)
		return (NULL);
	addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			*(unsigned int *)(addr + (y * line_len + x * (bpp / 8))) = color;
			x++;
		}
		y++;
	}
	return (img);
}

// Load minimap textures from ./textures/ folder
static int	load_minimap_textures(t_map *map_data, t_minimap *mini_map)
{
	t_mlx	*mlx_data;
	int		w;
	int		h;

	mlx_data = map_data->mlx_data;
	w = TILE_SIZE;
	h = TILE_SIZE;
	mini_map->wall_img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/mini_wall.xpm", &w, &h);
	if (!mini_map->wall_img)
		mini_map->wall_img = create_tile_img(mlx_data, TILE_SIZE, 0x505050);
	mini_map->floor_img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/mini_floor.xpm", &w, &h);
	if (!mini_map->floor_img)
		mini_map->floor_img = create_tile_img(mlx_data, TILE_SIZE, 0xD3D3D3);
	mini_map->void_img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/mini_void.xpm", &w, &h);
	if (!mini_map->void_img)
		mini_map->void_img = create_tile_img(mlx_data, TILE_SIZE, 0x1a1a1a);
	mini_map->player_img = mlx_xpm_file_to_image(mlx_data->mlx,
			"./textures/mini_plyr.xpm", &w, &h);
	if (!mini_map->player_img)
		mini_map->player_img = create_tile_img(mlx_data, TILE_SIZE, 0x00FF00);
	if (!mini_map->wall_img || !mini_map->floor_img
		|| !mini_map->void_img || !mini_map->player_img)
		return (0);
	return (1);
}

// Draw player indicator with direction arrow
static void	draw_player(t_mlx *mlx_data, int cx, int cy, float angle)
{
	int		px;
	int		py;
	int		r;
	float	rad;
	int		i;

	r = TILE_SIZE / 3;
	py = -r;
	while (py <= r)
	{
		px = -r;
		while (px <= r)
		{
			if (px * px + py * py <= r * r)
				mlx_pixel_put(mlx_data->mlx, mlx_data->win,
					cx + px, cy + py, 0x00FF00);
			px++;
		}
		py++;
	}
	rad = angle * 3.14159265359 / 180.0;
	i = 0;
	while (i < TILE_SIZE * 2 / 3)
	{
		mlx_pixel_put(mlx_data->mlx, mlx_data->win,
			cx + (int)(cos(rad) * i), cy + (int)(sin(rad) * i), 0xFF0000);
		mlx_pixel_put(mlx_data->mlx, mlx_data->win,
			cx + (int)(cos(rad) * i) + 1, cy + (int)(sin(rad) * i), 0xFF0000);
		mlx_pixel_put(mlx_data->mlx, mlx_data->win,
			cx + (int)(cos(rad) * i), cy + (int)(sin(rad) * i) + 1, 0xFF0000);
		mlx_pixel_put(mlx_data->mlx, mlx_data->win,
			cx + (int)(cos(rad) * i) - 1, cy + (int)(sin(rad) * i), 0xFF0000);
		mlx_pixel_put(mlx_data->mlx, mlx_data->win,
			cx + (int)(cos(rad) * i), cy + (int)(sin(rad) * i) - 1, 0xFF0000);
		i++;
	}
}

int	mini_map(t_map *map_data, t_minimap *mini_map)
{
	t_mlx		*mlx_data;
	int			x;
	int			y;
	int			tile;
	void		*img;
	static int	loaded = 0;
	float		off_x;
	float		off_y;

	mlx_data = map_data->mlx_data;
	if (!loaded && !load_minimap_textures(map_data, mini_map))
		return (0);
	loaded = 1;
	off_x = map_data->x_plyr - (int)map_data->x_plyr;
	off_y = map_data->y_plyr - (int)map_data->y_plyr;
	y = -1;
	while (++y <= MINIMAP_SIZE)
	{
		x = -1;
		while (++x <= MINIMAP_SIZE)
		{
			tile = get_map_tile(map_data, (int)map_data->x_plyr + x
					- MINIMAP_SIZE / 2, (int)map_data->y_plyr + y
					- MINIMAP_SIZE / 2);
			if (tile == '1')
				img = mini_map->wall_img;
			else if (tile == '0' || tile == 'N' || tile == 'S'
				|| tile == 'E' || tile == 'W')
				img = mini_map->floor_img;
			else
				img = mini_map->void_img;
			mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, img,
				x * TILE_SIZE + MINIMAP_OFFSET - (int)(off_x * TILE_SIZE),
				y * TILE_SIZE + MINIMAP_OFFSET - (int)(off_y * TILE_SIZE));
		}
	}
	draw_player(mlx_data, MINIMAP_OFFSET + (MINIMAP_SIZE * TILE_SIZE) / 2,
		MINIMAP_OFFSET + (MINIMAP_SIZE * TILE_SIZE) / 2, mlx_data->plyr_angle);
	return (1);
}

