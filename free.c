#include "cube.h"

int error(t_map *map_data, char *mes)
{
    printf("%s\n", mes);
    free_mapdata(map_data);
    return(0);
}
void free_files(t_files *files)
{
    if (files->c_file)
        free(files->c_file);
    if (files->f_file)
        free(files->f_file);
    if (files->ea_file)
        free(files->ea_file);
    if (files->we_file)
        free(files->we_file);
    if (files->no_file)
        free(files->no_file);
    if (files->so_file)
        free(files->so_file);
}

void free_mlx(t_mlx *mlx)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (mlx->image[i])
            mlx_destroy_image(mlx->mlx, mlx->image[i]);
        i++;
    }
    if (mlx->win)
        mlx_destroy_window(mlx->mlx, mlx->win);
    if (mlx->mlx)
    {
        mlx_destroy_display(mlx->mlx);
        free(mlx->mlx);
    }
    free(mlx);
}

void free_mapdata(t_map *map_data)
{
    if (map_data->map)
        ft_free_free(map_data->map);
    if (map_data->files)
        free_files(map_data->files);
    if (map_data->mlx_data)
        free_mlx(map_data->mlx_data);
}
