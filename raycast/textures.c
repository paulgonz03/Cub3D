#include "cube.h"
#include "minilibx-linux/mlx.h"

void paint_background(t_map *map_data, t_mlx *mlx_data)
{
	int x;
	int y;
	int pixel_position;

	mlx_data->img_data = (char *)mlx_get_data_addr(mlx_data->img, &mlx_data->bpp, &mlx_data->bpl, &mlx_data->order_bytes);
	y = -1;
	while (++y < 720)
	{
		x = -1;
		while (++x < 1080)
		{
			pixel_position = (y * mlx_data->bpl) + (x * (mlx_data->bpp/8)); // entre 8 para comvertir de bits a bytes
			mlx_data->img_data[pixel_position] = map_data->files->c_col_b;
			mlx_data->img_data[pixel_position + 1] = map_data->files->c_col_g;
			mlx_data->img_data[pixel_position + 2] = map_data->files->c_col_r;
			if (y > 359)
			{
				mlx_data->img_data[pixel_position] = map_data->files->f_col_b;
				mlx_data->img_data[pixel_position + 1] = map_data->files->f_col_g;
				mlx_data->img_data[pixel_position + 2] = map_data->files->f_col_r;
			}
		}
	}

}


int init_textures(t_files *files, t_mlx *mlx_data)
{
	int i;

	mlx_data->img = mlx_new_image(mlx_data->mlx, 1080, 720);
	mlx_data->img_data = (char *)mlx_get_data_addr(mlx_data->img, &mlx_data->bpp, &mlx_data->bpl, &mlx_data->order_bytes);
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
