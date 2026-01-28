#include "cube.h"
#include "minilibx-linux/mlx.h"

int closewin(t_mlx *mlx_data)
{
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	exit(0);
}

int key_press(int keycode, t_mlx *mlx_data)
{
	if (keycode == KEYD)
		mlx_data->keys->d = 1;
	if (keycode == KEYA)
		mlx_data->keys->a = 1;
	if (keycode == KEYS)
		mlx_data->keys->s = 1;
	if (keycode == KEYW)
		mlx_data->keys->w = 1;
	if (keycode == KEYESC)
		closewin(mlx_data);
	if (keycode == KEYLEFT)
		mlx_data->keys->left = 1;
	if (keycode == KEYRIGHT)
		mlx_data->keys->right = 1;
	return (0);
}

int key_release(int keycode, t_mlx *mlx_data)
{
	if (keycode == KEYD)
		mlx_data->keys->d = 0;
	if (keycode == KEYA)
		mlx_data->keys->a = 0;
	if (keycode == KEYS)
		mlx_data->keys->s = 0;
	if (keycode == KEYW)
		mlx_data->keys->w = 0;
	if (keycode == KEYESC)
		closewin(mlx_data);
	if (keycode == KEYLEFT)
		mlx_data->keys->left = 0;
	if (keycode == KEYRIGHT)
		mlx_data->keys->right = 0;
	return (0);
}

void key_moves(t_map *map_data, t_mlx *mlx_data)
{
	float angle;
	float fast;
	float new_y;
	float new_x;

	angle = mlx_data->plyr_angle * 3.1415926535 / 180.0f;
	fast = 0.35f;
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
	if (mlx_data->keys->left == 1)
	{
		mlx_data->plyr_angle -= 1.9f;
		if (mlx_data->plyr_angle < 0.0f)
			mlx_data->plyr_angle += 360.0f;
	}
	if (mlx_data->keys->right == 1)
	{
		mlx_data->plyr_angle += 1.9f;
		if (mlx_data->plyr_angle >= 0.0f)
			mlx_data->plyr_angle -= 360.0f;
	}
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
	return (0);
}
