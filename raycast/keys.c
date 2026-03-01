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
    float fast = 0.05f;
    float dir_x, dir_y;
    float side_x, side_y;
    float new_x, new_y;

    if (!mlx_data || !mlx_data->keys)
        return;

    /* ------------------ 1) APLICAR GIRO PRIMERO ------------------ */

	
    if (mlx_data->keys->left)
    {
        mlx_data->plyr_angle -= 1.9f;
        if (mlx_data->plyr_angle < 0)
            mlx_data->plyr_angle += 360;
    }
    if (mlx_data->keys->right)
    {
        mlx_data->plyr_angle += 1.9f;
        if (mlx_data->plyr_angle >= 360)
            mlx_data->plyr_angle -= 360;
    }

    /* ------------------ 2) RECALCULAR ANGULO ------------------ */

    angle = mlx_data->plyr_angle * PI / 180.0f;

    /* vector frontal */
    dir_x = cos(angle);
    dir_y = sin(angle);

    /* vector lateral perpendicular */
    side_x = -dir_y;
    side_y =  dir_x;

    /* ------------------ 3) MOVER ------------------ */

    if (mlx_data->keys->w)
    {
        new_x = map_data->x_plyr + dir_x * fast;
        new_y = map_data->y_plyr + dir_y * fast;
        if (check_walls(mlx_data, new_y, new_x, map_data))
        {
            map_data->x_plyr = new_x;
            map_data->y_plyr = new_y;
        }
    }

    if (mlx_data->keys->s)
    {
        new_x = map_data->x_plyr - dir_x * fast;
        new_y = map_data->y_plyr - dir_y * fast;
        if (check_walls(mlx_data, new_y, new_x, map_data))
        {
            map_data->x_plyr = new_x;
            map_data->y_plyr = new_y;
        }
    }

    if (mlx_data->keys->d)
    {
        new_x = map_data->x_plyr + side_x * fast;
        new_y = map_data->y_plyr + side_y * fast;
        if (check_walls(mlx_data, new_y, new_x, map_data))
        {
            map_data->x_plyr = new_x;
            map_data->y_plyr = new_y;
        }
    }

    if (mlx_data->keys->a)
    {
        new_x = map_data->x_plyr - side_x * fast;
        new_y = map_data->y_plyr - side_y * fast;
        if (check_walls(mlx_data, new_y, new_x, map_data))
        {
            map_data->x_plyr = new_x;
            map_data->y_plyr = new_y;
        }
    }
}
int mouse(int x, int y, t_mlx *mlx)
{
    mlx->mouse = x;   // solo guardamos
    (void)y;
    return (0);
}

void apply_mouse_rotation(t_mlx *mlx)
{
    int deadzone = 50; // tamaño del cuadrado central
    int center_x = (WIDTH / 2)- deadzone-100;
    float sens = 0.003f; // sensibilidad fina
    int delta;

    // Si el ratón está dentro del cuadrado central → no girar
    if (mlx->mouse > center_x - deadzone &&
        mlx->mouse < center_x + deadzone)
        return;

    // Si está fuera → girar según la distancia al centro
    delta = mlx->mouse - center_x;

    mlx->plyr_angle += delta * sens;

    if (mlx->plyr_angle < 0)
        mlx->plyr_angle += 360;
    if (mlx->plyr_angle >= 360)
        mlx->plyr_angle -= 360;
}

