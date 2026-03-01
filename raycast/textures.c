#include "cube.h"
#include "minilibx-linux/mlx.h"

static int  load_single_texture(t_mlx *mlx, char *path, int id)
{
    mlx->image[id] = mlx_xpm_file_to_image(
            mlx->mlx,
            path,
            &mlx->tex_width[id],
            &mlx->tex_height[id]);

    if (!mlx->image[id])
        return (0);

    mlx->texture_data[id] = (int *)mlx_get_data_addr(
            mlx->image[id],
            &mlx->tex_bpp[id],
            &mlx->tex_bpl[id],
            &mlx->tex_endian[id]);

    return (1);
}

int init_textures(t_files *files, t_mlx *mlx)
{
    if (!files->no_file || !files->so_file
        || !files->we_file || !files->ea_file)
        return (0);

    /* Imagen principal (framebuffer) */
    mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    if (!mlx->img)
        return (0);

    mlx->img_data = mlx_get_data_addr(
            mlx->img,
            &mlx->bpp,
            &mlx->bpl,
            &mlx->order_bytes);

    /* Cargar texturas */
    if (!load_single_texture(mlx, files->no_file, NO))
        return (0);
    if (!load_single_texture(mlx, files->so_file, SO))
        return (0);
    if (!load_single_texture(mlx, files->we_file, WE))
        return (0);
    if (!load_single_texture(mlx, files->ea_file, EA))
        return (0);

    return (1);
}
void    paint_background(t_map *map_data, t_mlx *mlx_data)
{
    int x;
    int y;
    int color_floor;
    int color_ceiling;

    color_floor = (map_data->files->f_col_r << 16)
        | (map_data->files->f_col_g << 8)
        | map_data->files->f_col_b;

    color_ceiling = (map_data->files->c_col_r << 16)
        | (map_data->files->c_col_g << 8)
        | map_data->files->c_col_b;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            if (y < HALF_H)
                put_pixel(mlx_data, x, y, color_ceiling);
            else
                put_pixel(mlx_data, x, y, color_floor);
            x++;
        }
        y++;
    }
}
