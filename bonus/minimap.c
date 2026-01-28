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
			if (x == 0 || y == 0 || x == size - 1 || y == size - 1)
				*(unsigned int *)(addr + (y * line_len + x * (bpp / 8))) = 0x202020;
			else
				*(unsigned int *)(addr + (y * line_len + x * (bpp / 8))) = color;
			x++;
		}
		y++;
	}
	return (img);
}

// Load or create minimap textures
static int	load_minimap_textures(t_map *map_data, t_minimap *mini_map)
{
	t_mlx	*mlx_data;
	int		width;
	int		height;

	mlx_data = map_data->mlx_data;
	width = TILE_SIZE;
	height = TILE_SIZE;
	
	// Try to load textures from .xpm files, use colored fallback if they fail
	mini_map->wall_img = mlx_xpm_file_to_image(mlx_data->mlx, 
		"./textures/mini_wall.xpm", &width, &height);
	if (!mini_map->wall_img)
		mini_map->wall_img = create_tile_img(mlx_data, TILE_SIZE, 0x505050);
		
	mini_map->floor_img = mlx_xpm_file_to_image(mlx_data->mlx, 
		"./textures/mini_floor.xpm", &width, &height);
	if (!mini_map->floor_img)
		mini_map->floor_img = create_tile_img(mlx_data, TILE_SIZE, 0xD3D3D3);
		
	mini_map->void_img = mlx_xpm_file_to_image(mlx_data->mlx, 
		"./textures/mini_void.xpm", &width, &height);
	if (!mini_map->void_img)
		mini_map->void_img = create_tile_img(mlx_data, TILE_SIZE, 0x1a1a1a);
		
	mini_map->player_img = mlx_xpm_file_to_image(mlx_data->mlx, 
		"./textures/mini_player.xpm", &width, &height);
	if (!mini_map->player_img)
		mini_map->player_img = create_tile_img(mlx_data, TILE_SIZE, 0xD3D3D3);
	
	mini_map->img_width = TILE_SIZE;
	mini_map->img_height = TILE_SIZE;
	
	if (!mini_map->wall_img || !mini_map->floor_img || 
		!mini_map->void_img || !mini_map->player_img)
		return (0);
	return (1);
}

// Draw minecraft-style wooden border
static void	draw_border(t_mlx *mlx_data, int size, int tile_size)
{
	int	i;
	int	max;
	int	t;
	int	color;
	int	pattern;

	max = size * tile_size;
	i = 0;
	while (i < max)
	{
		t = 0;
		while (t < 6)
		{
			// Create wood grain pattern
			pattern = (i / 4 + t) % 3;
			
			if (t == 0 || t == 5)
				color = 0x4A2511; // Dark brown border
			else if (pattern == 0)
				color = 0x8B4513; // Saddle brown
			else if (pattern == 1)
				color = 0xA0522D; // Sienna
			else
				color = 0x6B3410; // Medium brown
			
			// Top border
			mlx_pixel_put(mlx_data->mlx, mlx_data->win, 
				i + MINIMAP_OFFSET, t + MINIMAP_OFFSET, color);
			// Bottom border
			mlx_pixel_put(mlx_data->mlx, mlx_data->win, 
				i + MINIMAP_OFFSET, max - 1 - t + MINIMAP_OFFSET, color);
			// Left border
			mlx_pixel_put(mlx_data->mlx, mlx_data->win, 
				t + MINIMAP_OFFSET, i + MINIMAP_OFFSET, color);
			// Right border
			mlx_pixel_put(mlx_data->mlx, mlx_data->win, 
				max - 1 - t + MINIMAP_OFFSET, i + MINIMAP_OFFSET, color);
			t++;
		}
		i++;
	}
	
	// Add corner decorations (darker)
	int corner_size = 6;
	int cx, cy;
	for (cy = 0; cy < corner_size; cy++)
	{
		for (cx = 0; cx < corner_size; cx++)
		{
			color = 0x3D1F0F; // Very dark brown for corners
			// Top-left corner
			mlx_pixel_put(mlx_data->mlx, mlx_data->win,
				cx + MINIMAP_OFFSET, cy + MINIMAP_OFFSET, color);
			// Top-right corner
			mlx_pixel_put(mlx_data->mlx, mlx_data->win,
				max - 1 - cx + MINIMAP_OFFSET, cy + MINIMAP_OFFSET, color);
			// Bottom-left corner
			mlx_pixel_put(mlx_data->mlx, mlx_data->win,
				cx + MINIMAP_OFFSET, max - 1 - cy + MINIMAP_OFFSET, color);
			// Bottom-right corner
			mlx_pixel_put(mlx_data->mlx, mlx_data->win,
				max - 1 - cx + MINIMAP_OFFSET, max - 1 - cy + MINIMAP_OFFSET, color);
		}
	}
}

// Draw simple player indicator at center
static void	draw_player(t_mlx *mlx_data, int center_x, int center_y, float angle)
{
	int	px, py, radius, i;
	float angle_rad, dir_x, dir_y;
	int arrow_len, arrow_x, arrow_y;

	// Draw green circle
	radius = TILE_SIZE / 3;
	py = -radius;
	while (py <= radius)
	{
		px = -radius;
		while (px <= radius)
		{
			if (px * px + py * py <= radius * radius)
				mlx_pixel_put(mlx_data->mlx, mlx_data->win,
					center_x + px, center_y + py, 0x00FF00);
			px++;
		}
		py++;
	}
	
	// Draw red direction arrow (wider)
	angle_rad = angle * 3.14159265359 / 180.0;
	dir_x = cos(angle_rad);
	dir_y = sin(angle_rad);
	arrow_len = TILE_SIZE / 2;
	i = 0;
	while (i < arrow_len)
	{
		arrow_x = (int)(dir_x * i);
		arrow_y = (int)(dir_y * i);
		// Draw thicker arrow
		mlx_pixel_put(mlx_data->mlx, mlx_data->win,
			center_x + arrow_x, center_y + arrow_y, 0xFF0000);
		mlx_pixel_put(mlx_data->mlx, mlx_data->win,
			center_x + arrow_x + 1, center_y + arrow_y, 0xFF0000);
		mlx_pixel_put(mlx_data->mlx, mlx_data->win,
			center_x + arrow_x - 1, center_y + arrow_y, 0xFF0000);
		mlx_pixel_put(mlx_data->mlx, mlx_data->win,
			center_x + arrow_x, center_y + arrow_y + 1, 0xFF0000);
		mlx_pixel_put(mlx_data->mlx, mlx_data->win,
			center_x + arrow_x, center_y + arrow_y - 1, 0xFF0000);
		i++;
	}
}

int	mini_map(t_map *map_data, t_minimap *mini_map)
{
	t_mlx	*mlx_data;
	int		x, y, map_x, map_y, tile;
	void	*img;
	static int loaded = 0;
	int		center_x, center_y;

	mlx_data = map_data->mlx_data;
	if (!loaded && !load_minimap_textures(map_data, mini_map))
		return (0);
	loaded = 1;
	
	// Draw map tiles around player
	y = -1;
	while (++y < MINIMAP_SIZE)
	{
		x = -1;
		while (++x < MINIMAP_SIZE)
		{
			map_x = (int)map_data->x_plyr + (x - MINIMAP_SIZE / 2);
			map_y = (int)map_data->y_plyr + (y - MINIMAP_SIZE / 2);
			tile = get_map_tile(map_data, map_x, map_y);
			
			if (tile == '1')
				img = mini_map->wall_img;
			else if (tile == '0' || tile == 'N' || tile == 'S'
				|| tile == 'E' || tile == 'W')
				img = mini_map->floor_img;
			else
				img = mini_map->void_img;
			
			mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, img,
				x * TILE_SIZE + MINIMAP_OFFSET, y * TILE_SIZE + MINIMAP_OFFSET);
		}
	}
	
	// Draw player at center
	center_x = (MINIMAP_SIZE / 2) * TILE_SIZE + MINIMAP_OFFSET + TILE_SIZE / 2;
	center_y = (MINIMAP_SIZE / 2) * TILE_SIZE + MINIMAP_OFFSET + TILE_SIZE / 2;
	draw_player(mlx_data, center_x, center_y, mlx_data->plyr_angle);
	
	draw_border(mlx_data, MINIMAP_SIZE, TILE_SIZE);
	return (1);
}
