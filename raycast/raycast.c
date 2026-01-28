#include "cube.h"
#include "minilibx-linux/mlx.h"

void init_data(t_map *map_data)
{
	map_data->mlx_data->mouse = -1;
	if (map_data->view_player == 'E')
		map_data->mlx_data->plyr_angle = 0;
	else if (map_data->view_player == 'N')
		map_data->mlx_data->plyr_angle = 270;
	else if (map_data->view_player == 'W')
		map_data->mlx_data->plyr_angle = 180;
	else if (map_data->view_player == 'S')
		map_data->mlx_data->plyr_angle = 90;
	if (!init_textures(map_data->files, map_data->mlx_data))
	{
		printf("Error: init textures\n");
		exit(0);
	}
	map_data->mlx_data->win = mlx_new_window(map_data->mlx_data->mlx, 1080, 720, "Cub3D");
}

int	check_walls(t_mlx *mlx_data, float y, float x, t_map *map_data)
{
	int map_y;
	int map_x;

	map_y = (int)y;
	map_x = (int)x;
	if (map_y < 0 || map_y >= map_data->lines)
		return (0);
	if (map_x < 0 || !map_data->map[map_y])
		return (0);
	if (map_x >= (int)ft_strlen(map_data->map[map_y]))
		return (0);
	if (map_data->map[map_y][map_x] == '1' || map_data->map[map_y][map_x] == ' ')
		return (0);
	return (1);
	(void)mlx_data;
}

void key_moves(t_map *map_data, t_mlx *mlx_data)
{
	float angle;
	float fast;
	float new_y;
	float new_x;

	angle = mlx_data->plyr_angle * 3.1415926535 / 180.0f;
	fast = 0.08f;
	if (mlx_data->keys->w == 1)
	{
		new_x = map_data->x_plyr + cos(angle) * fast;
		new_y = map_data->y_plyr + sin(angle) * fast;
		if (check_walls(mlx_data, new_y, new_x, map_data))
		{
			map_data->x_plyr = new_x;
			map_data->y_plyr = new_y;
		}
	}
	if (mlx_data->keys->s == 1)
	{
		new_x = map_data->x_plyr - cos(angle) * fast;
		new_y = map_data->y_plyr - sin(angle) * fast;
		if (check_walls(mlx_data, new_y, new_x, map_data))
		{
			map_data->x_plyr = new_x;
			map_data->y_plyr = new_y;
		}
	}
	if (mlx_data->keys->a == 1)
	{
		new_x = map_data->x_plyr - cos(angle + 3.1415926535 / 2) * fast;
		new_y = map_data->y_plyr - sin(angle + 3.1415926535 / 2) * fast;
		if (check_walls(mlx_data, new_y, new_x, map_data))
		{
			map_data->x_plyr = new_x;
			map_data->y_plyr = new_y;
		}
	}
	if (mlx_data->keys->d == 1)
	{
		new_x = map_data->x_plyr + cos(angle + 3.1415926535 / 2) * fast;
		new_y = map_data->y_plyr + sin(angle + 3.1415926535 / 2) * fast;
		if (check_walls(mlx_data, new_y, new_x, map_data))
		{
			map_data->x_plyr = new_x;
			map_data->y_plyr = new_y;
		}
	}
}

int game_loop(void *data)
{
	t_map *map_data;

	map_data = data;
	key_moves(map_data, map_data->mlx_data);
	paint_background(map_data, map_data->mlx_data);
	mlx_put_image_to_window(map_data->mlx_data->mlx, map_data->mlx_data->win, map_data->mlx_data->img, 0, 0);
	mini_map(map_data, map_data->mlx_data->mini_map);
	return (1);
}

int mouse(int x, int y, t_mlx *mlx_data)
{
	float angle;

	if (mlx_data->mouse != -1)
	{
		angle = (x - mlx_data->mouse) * 0.2f;
		mlx_data->plyr_angle += angle;
		if (mlx_data->plyr_angle < 0) // normalizar el angulo si es -
			mlx_data->plyr_angle += 360.0f;
		if (mlx_data->plyr_angle < 0) // normalizar el angulo si es mas de de 360
			mlx_data->plyr_angle -= 360.0f;
	}
	mlx_data->mouse = x;
	(void)y;
	return(0);
}

int raycast(t_map *map_data)
{
	map_data->mlx_data = ft_calloc(1, sizeof(t_mlx));
	map_data->mlx_data->mini_map = ft_calloc(1, sizeof(t_minimap));
	map_data->mlx_data->keys = ft_calloc(1, sizeof(t_keys));
	map_data->mlx_data->mlx = mlx_init();

	init_data(map_data);
	mlx_hook(map_data->mlx_data->win, 2, 1L << 0, key_press, map_data->mlx_data);
	mlx_key_hook(map_data->mlx_data->win, key_release, map_data->mlx_data);
	mlx_hook(map_data->mlx_data->win, 6, 1L << 6, mouse, map_data->mlx_data);
	mlx_loop_hook(map_data->mlx_data->mlx, game_loop, map_data);
	mlx_hook(map_data->mlx_data->win, CLOSEWIN, 0, closewin, map_data->mlx_data);
	mlx_loop(map_data->mlx_data->mlx);
	return (1);
}
