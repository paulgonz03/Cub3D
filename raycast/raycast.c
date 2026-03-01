#include "cube.h"
#include "minilibx-linux/mlx.h"
#include <sys/time.h>

long    get_time_ms(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

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
	if (!map_data->mlx_data->win)
	{
		printf("Error: mlx_new_window failed\n");
		exit(1);
	}
	map_data->sprite = NULL;
	load_torches_from_map(map_data, map_data->mlx_data);
}

static int is_wall(t_map *map_data, int map_y, int map_x)
{
    if (map_y < 0 || map_y >= map_data->lines)
        return (1);
    if (map_x < 0)
        return (1);
    if (map_x >= (int)ft_strlen(map_data->map[map_y]))
        return (1);
    if (map_data->map[map_y][map_x] == '1'
        || map_data->map[map_y][map_x] == ' ')
        return (1);
    return (0);
}



int	check_walls(t_mlx *mlx_data, float y, float x, t_map *map_data)
{
	float m;

	m = 0.2f;
	if (y < 0 || x < 0)
    	return (0);
	if (y >= map_data->lines)
    	return (0);
	if (is_wall(map_data, (int)(y - m), (int)(x - m)))
		return (0);
	if (is_wall(map_data, (int)(y - m), (int)(x + m)))
		return (0);
	if (is_wall(map_data, (int)(y + m), (int)(x - m)))
		return (0);
	if (is_wall(map_data, (int)(y + m), (int)(x + m)))
		return (0);
	return (1);
	(void)mlx_data;
}
int game_loop(void *data)
{
    t_map   *map;
    t_mlx   *mlx;
    static long last_frame = 0;
    long now = get_time_ms();

    if (now - last_frame < 16)   // ~60 FPS
        return (0);
    last_frame = now;

    map = data;
    mlx = map->mlx_data;

    key_moves(map, mlx);
    apply_mouse_rotation(mlx);

    paint_background(map, mlx);

    // raycasting + z-buffer
    rays(map, mlx);

    // sprites
    t_sprite *sp = map->sprite;
    while (sp)
    {
        update_sprite_animation(sp, 0.016f);
        draw_sprite(mlx, map, sp, map->zbuffer);
        sp = sp->next;
    }

    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    mini_map(map, mlx->mini_map);

    return (1);
}


int raycast(t_map *map_data)
{
    map_data->mlx_data = ft_calloc(1, sizeof(t_mlx));
    map_data->mlx_data->mini_map = ft_calloc(1, sizeof(t_minimap));
    map_data->mlx_data->keys = ft_calloc(1, sizeof(t_keys));
    map_data->mlx_data->mlx = mlx_init();
	if (!map_data->mlx_data->mlx)
	{
    	printf("Error: mlx_init failed\n");
    	exit(1);
	}
    init_data(map_data);
    mlx_hook(map_data->mlx_data->win, 2, 1L << 0, key_press, map_data->mlx_data);
    mlx_hook(map_data->mlx_data->win, 3, 1L << 1, key_release, map_data->mlx_data);
    mlx_hook(map_data->mlx_data->win, 6, 1L << 6, mouse, map_data->mlx_data);
    mlx_loop_hook(map_data->mlx_data->mlx, game_loop, map_data);
    mlx_hook(map_data->mlx_data->win, CLOSEWIN, 0, closewin, map_data->mlx_data);
    mlx_loop(map_data->mlx_data->mlx);
    return (1);
}

