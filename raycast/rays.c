#include "cube.h"
#include "minilibx-linux/mlx.h"
#include <math.h>

static float    deg_to_rad(float a)
{
    return (a * PI / 180.0f);
}
int apply_shading(int color, float dist)
{
    float shade;
    int r, g, b;

    shade = 1.0f / (1.0f + dist * 0.1f);

    if (shade < 0.2f)
        shade = 0.2f;

    r = ((color >> 16) & 0xFF) * shade;
    g = ((color >> 8) & 0xFF) * shade;
    b = (color & 0xFF) * shade;

    return (r << 16) | (g << 8) | b;
}

void    put_pixel(t_mlx *mlx, int x, int y, int color)
{
    int pos;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
    pos = y * mlx->bpl + x * (mlx->bpp / 8);
    mlx->img_data[pos] = color & 0xFF;
    mlx->img_data[pos + 1] = (color >> 8) & 0xFF;
    mlx->img_data[pos + 2] = (color >> 16) & 0xFF;
}

static int  is_wall_block(t_map *map, int y, int x)
{
    if (y < 0 || y >= map->lines)
        return (1);
    if (x < 0)
        return (1);
    if (x >= (int)ft_strlen(map->map[y]))
        return (1);
    if (map->map[y][x] == '1' || map->map[y][x] == ' ')
        return (1);
    return (0);
}

/* ---------------------- TEXTURAS ---------------------------- */

static int  select_texture(int side, float ray_dir_x, float ray_dir_y)
{
    if (side == 0)
        return (ray_dir_x > 0 ? EA : WE);
    return (ray_dir_y > 0 ? SO : NO);
}

static int  get_tex_x(int tex_w, int side, float ray_dir_x,
                        float ray_dir_y, float wall_x)
{
    int x;

    wall_x -= floorf(wall_x);
    x = (int)(wall_x * (float)tex_w);

    if (side == 0 && ray_dir_x < 0)
        x = tex_w - 1 - x;
    if (side == 1 && ray_dir_y > 0)
        x = tex_w - 1 - x;

    if (x < 0)
        x = 0;
    if (x >= tex_w)
        x = tex_w - 1;
    return (x);
}

static int  get_tex_y(int y, int draw_start_real, int line_h, int tex_h)
{
    float   pos;
    int     ty;

    pos = (float)(y - draw_start_real) / (float)line_h;
    if (pos < 0.0f)
        pos = 0.0f;
    if (pos > 1.0f)
        pos = 1.0f;
    ty = (int)(pos * tex_h);
    if (ty < 0)
        ty = 0;
    if (ty >= tex_h)
        ty = tex_h - 1;
    return (ty);
}

static void draw_column(t_mlx *mlx, int col, int side,
    float perp_dist, float ray_dir_x,
    float ray_dir_y, float wall_x)
{
float   line_h_f;
int     line_h;
int     draw_start_real;
int     draw_start;
int     draw_end;
int     id;
int     tex_x;
int     y;
int     tex_y;
int     color;

if (perp_dist < 0.0001f)
perp_dist = 0.0001f;

line_h_f = (float)HEIGHT / perp_dist;
line_h = (int)line_h_f;

draw_start_real = HEIGHT / 2 - line_h / 2;
draw_start = draw_start_real;
draw_end = draw_start_real + line_h;

if (draw_start < 0)
draw_start = 0;
if (draw_end > HEIGHT)
draw_end = HEIGHT;

id = select_texture(side, ray_dir_x, ray_dir_y);
tex_x = get_tex_x(mlx->tex_width[id], side, ray_dir_x, ray_dir_y, wall_x);

y = draw_start;
while (y < draw_end)
{
tex_y = get_tex_y(y, draw_start_real, line_h, mlx->tex_height[id]);
color = mlx->texture_data[id][tex_y * mlx->tex_width[id] + tex_x];

color = apply_shading(color, perp_dist);

put_pixel(mlx, col, y, color);
y++;
}
}


/* ---------------------- RAYO + DDA -------------------------- */

// ---------------------- RAYO + DDA --------------------------

// ray de UNA columna
static void cast_ray(t_map *map, t_mlx *mlx, int col)
{
    float   ray_angle_deg;
    float   rad;
    float   ray_dir_x;
    float   ray_dir_y;
    int     map_x;
    int     map_y;
    float   delta_dist_x;
    float   delta_dist_y;
    float   side_dist_x;
    float   side_dist_y;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;
    float   dist;
    float   perp_dist;
    float   wall_x;
    float   player_rad;

    ray_angle_deg = (float)mlx->plyr_angle - 30.0f
        + 60.0f * ((float)col / (float)WIDTH);
    if (ray_angle_deg < 0.0f)
        ray_angle_deg += 360.0f;
    if (ray_angle_deg >= 360.0f)
        ray_angle_deg -= 360.0f;

    rad = deg_to_rad(ray_angle_deg);
    ray_dir_x = cosf(rad);
    ray_dir_y = sinf(rad);

    map_x = (int)map->x_plyr;
    map_y = (int)map->y_plyr;

    delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabsf(1.0f / ray_dir_x);
    delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabsf(1.0f / ray_dir_y);

    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (map->x_plyr - (float)map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = ((float)map_x + 1.0f - map->x_plyr) * delta_dist_x;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (map->y_plyr - (float)map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = ((float)map_y + 1.0f - map->y_plyr) * delta_dist_y;
    }

    hit = 0;
    while (!hit)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }
        if (is_wall_block(map, map_y, map_x))
            hit = 1;
    }

    if (side == 0)
        dist = ((float)map_x - map->x_plyr + (1 - step_x) / 2.0f) / ray_dir_x;
    else
        dist = ((float)map_y - map->y_plyr + (1 - step_y) / 2.0f) / ray_dir_y;

    player_rad = deg_to_rad((float)mlx->plyr_angle);
    perp_dist = dist * cosf(rad - player_rad);

    // Z-BUFFER: guardar distancia perpendicular
    map->zbuffer[col] = perp_dist;

    // wall_x con dist real
    if (side == 0)
        wall_x = map->y_plyr + dist * ray_dir_y;
    else
        wall_x = map->x_plyr + dist * ray_dir_x;

    wall_x -= floorf(wall_x);

    draw_column(mlx, col, side, perp_dist, ray_dir_x, ray_dir_y, wall_x);
}

// bucle de TODAS las columnas
void rays(t_map *map, t_mlx *mlx)
{
    int col;

    col = 0;
    while (col < WIDTH)
    {
        cast_ray(map, mlx, col);
        col++;
    }
}
