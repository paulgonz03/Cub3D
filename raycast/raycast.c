#include "cube.h"
#include "minilibx-linux/mlx.h"

int init_textures(t_files *files, t_mlx *mlx_data)
{
	int i;

	mlx_data->img = mlx_new_image(mlx_data->mlx, 1080, 720);
	mlx_data->img_data = mlx_get_data_addr(mlx_data->img, &mlx_data->bpp, &mlx_data->bpl, &mlx_data->order_bytes);
	mlx_data->image[NO] = mlx_xpm_file_to_image(mlx_data->mlx, files->no_file, &mlx_data->img_width, &mlx_data->img_height);
	mlx_data->image[SO] = mlx_xpm_file_to_image(mlx_data->mlx, files->so_file, &mlx_data->img_width, &mlx_data->img_height);
	mlx_data->image[WE] = mlx_xpm_file_to_image(mlx_data->mlx, files->we_file, &mlx_data->img_width, &mlx_data->img_height);
	mlx_data->image[EA] = mlx_xpm_file_to_image(mlx_data->mlx, files->ea_file, &mlx_data->img_width, &mlx_data->img_height);
	if (!mlx_data->image[NO] || !mlx_data->image[SO] || !mlx_data->image[WE] || !mlx_data->image[EA])
		return (0);
	i = 0;
	while (i < 4)
	{
		mlx_data->texture_data[i] = (int *)mlx_get_data_addr(mlx_data->image[i], &mlx_data->bpp, &mlx_data->bpl, &mlx_data->order_bytes);
		i++;
	}
	return (1);
}

int closewin(t_mlx *mlx_data)
{
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	exit(0);
}
int keycodes(int keycode, t_map *map_data)
{
	// if (keycode == KEYD || keycode == KEYRIGHT)
	// 	moveright(map_data);
	// if (keycode == KEYA || keycode == KEYLEFT)
	// 	moveleft(map_data);
	// if (keycode == KEYS || keycode == KEYDOWN)
	// 	movedown(map_data);
	// if (keycode == KEYW || keycode == KEYUP)
	// 	moveup(map_data);
	if (keycode == KEYESC)
		closewin(map_data->mlx_data);
	return(0);
}

int raycast(t_map *map_data)
{
	map_data->mlx_data = ft_calloc(1, sizeof(t_mlx));
	map_data->mlx_data->mlx = mlx_init();
	if (!init_textures(map_data->files, map_data->mlx_data))
	{
		printf("Error: init textures\n");
		exit(0);
	}
	map_data->mlx_data->win = mlx_new_window(map_data->mlx_data->mlx,
											 (map_data->x_limit - 1) * 50, map_data->y_limit * 50, "Cub3D");
	
	mlx_hook(map_data->mlx_data->win, CLOSEWIN, 0, closewin, map_data->mlx_data);
	mlx_key_hook(map_data->mlx_data->win, keycodes, map_data);
	mlx_loop(map_data->mlx_data->mlx);
	return (1);
}
