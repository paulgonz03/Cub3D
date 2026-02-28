#include "cube.h"
#include "minilibx-linux/mlx.h"

// crea una imagen cuadrada de color solido
void	*create_tile_img(t_mlx *mlx_data, int size, int color)
{
	void	*img;
	char	*addr;
	int		data[3];
	int		x;
	int		y;

	img = mlx_new_image(mlx_data->mlx, size, size);
	if (!img)
		return (NULL);
	addr = mlx_get_data_addr(img, &data[0], &data[1], &data[2]);
	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size)
			*(unsigned int *)(addr + (y * data[1] + x * (data[0] / 8))) = color;
	}
	return (img);
}

// carga una textura o crea fallback
void	*load_texture(t_mlx *mlx, char *path, int color)
{
	void	*img;
	int		w;
	int		h;

	w = TILE_SIZE;
	h = TILE_SIZE;
	img = mlx_xpm_file_to_image(mlx->mlx, path, &w, &h);
	if (!img)
		img = create_tile_img(mlx, TILE_SIZE, color);
	return (img);
}

// cargan la texturas de minimapa de la carpeta
int	load_minimap_textures(t_map *map_data, t_minimap *mini_map)
{
	t_mlx	*mlx_data;

	mlx_data = map_data->mlx_data;
	mini_map->wall_img = load_texture(mlx_data, "./textures/mini_wall.xpm",
			0x505050);
	mini_map->floor_img = load_texture(mlx_data, "./textures/mini_floor.xpm",
			0xD3D3D3);
	mini_map->void_img = load_texture(mlx_data, "./textures/mini_void.xpm",
			0x1a1a1a);
	mini_map->player_img = load_texture(mlx_data, "./textures/mini_plyr.xpm",
			0x00FF00);
	if (!mini_map->wall_img || !mini_map->floor_img || !mini_map->void_img
		|| !mini_map->player_img)
		return (0);
	return (1);
}

// dibuja el circulo del jugador
void	draw_circle(t_mlx *mlx, int cx, int cy)
{
	int	px;
	int	py;
	int	r;

	r = TILE_SIZE / 3;
	py = -r - 1;
	while (++py <= r)
	{
		px = -r;
		while (px <= r)
		{
			if (px * px + py * py <= r * r)
				mlx_pixel_put(mlx->mlx, mlx->win, cx + px, cy + py, 0x00FF00);
			px++;
		}
	}
}

// dibuja la linea de direccion
void	draw_direction(t_mlx *mlx, int cx, int cy, float angle)
{
	float	rad;
	int		i;
	int		dx;
	int		dy;

	rad = angle * PI / 180.0;
	i = -1;
	while (++i < TILE_SIZE * 2 / 3)
	{
		dx = (int)(cos(rad) * i);
		dy = (int)(sin(rad) * i);
		mlx_pixel_put(mlx->mlx, mlx->win, cx + dx, cy + dy, 0xFF0000);
		mlx_pixel_put(mlx->mlx, mlx->win, cx + dx + 1, cy + dy, 0xFF0000);
		mlx_pixel_put(mlx->mlx, mlx->win, cx + dx, cy + dy + 1, 0xFF0000);
		mlx_pixel_put(mlx->mlx, mlx->win, cx + dx - 1, cy + dy, 0xFF0000);
		mlx_pixel_put(mlx->mlx, mlx->win, cx + dx, cy + dy - 1, 0xFF0000);
	}
}
