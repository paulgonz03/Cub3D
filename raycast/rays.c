#include "cube.h"
#include "minilibx-linux/mlx.h"
#include <math.h>

typedef struct s_hit
{
    float   x;
    float   y;
    float   dist;
    int     vertical;
}   t_hit;

static float    deg_to_rad(float a)
{
    return (a * PI / 180.0f);
}

void put_pixel(t_mlx *mlx, int x, int y, int color)
{
    int pos;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
    pos = y * mlx->bpl + x * (mlx->bpp / 8);
    mlx->img_data[pos] = color & 0xFF;
    mlx->img_data[pos + 1] = (color >> 8) & 0xFF;
    mlx->img_data[pos + 2] = (color >> 16) & 0xFF;
}

/* ------------------------------------------------------------ */
/*   DDA HORIZONTAL                                              */
/* ------------------------------------------------------------ */

static void horizontal_hit(t_map *map, float rad, t_hit *h)
{
    float   ya;
    float   xa;
    float   y;
    float   x;

    if (sin(rad) > 0)
        y = floor(map->y_plyr) + 1;
    else
        y = floor(map->y_plyr) - 0.0001f;
    ya = (sin(rad) > 0) ? 1 : -1;
    xa = ya / tan(rad);
    x = map->x_plyr + (y - map->y_plyr) / tan(rad);
    while (x >= 0 && y >= 0
        && (int)y < map->lines
        && map->map[(int)y]
        && (int)x >= 0
        && (int)x < (int)ft_strlen(map->map[(int)y])
        && map->map[(int)y][(int)x] != '1')
    {
        x += xa;
        y += ya;
    }
    h->x = x;
    h->y = y;
    h->dist = hypotf(x - map->x_plyr, y - map->y_plyr);
    h->vertical = 0;
}


/* ------------------------------------------------------------ */
/*   DDA VERTICAL                                                */
/* ------------------------------------------------------------ */

static int is_inside_map(t_map *map, int y, int x)
{
    if (y < 0 || y >= map->lines)
        return (0);
    if (!map->map[y])
        return (0);
    int len = ft_strlen(map->map[y]);
    if (x < 0 || x >= len)
        return (0);
    return (1);
}
static void vertical_hit(t_map *map, float rad, t_hit *v)
{
    float xa;
    float ya;
    float x;
    float y;

    if (cos(rad) > 0)
        x = floor(map->x_plyr) + 1;
    else
        x = floor(map->x_plyr) - 0.0001f;

    xa = (cos(rad) > 0) ? 1 : -1;
    ya = xa * tan(rad);
    y = map->y_plyr + (x - map->x_plyr) * tan(rad);

    while (is_inside_map(map, (int)y, (int)x)
        && map->map[(int)y][(int)x] != '1')
    {
        x += xa;
        y += ya;
    }

    v->x = x;
    v->y = y;
    v->dist = hypotf(x - map->x_plyr, y - map->y_plyr);
    v->vertical = 1;
}



/* ------------------------------------------------------------ */
/*   CAST RAY (DDA REAL)                                         */
/* ------------------------------------------------------------ */

static void cast_single_ray(t_map *map, t_mlx *mlx, int col, t_ray *ray)
{
    float   rad;
    t_hit   h;
    t_hit   v;

    ray->ray_angle = mlx->plyr_angle - 30.0f
        + ((float)col / 1080.0f) * 60.0f;
    rad = deg_to_rad(ray->ray_angle);

    horizontal_hit(map, rad, &h);
    vertical_hit(map, rad, &v);

    if (h.dist < v.dist)
    {
        ray->wall_x = h.x;
        ray->wall_y = h.y;
        ray->distance = h.dist;
        ray->hit_vertical = 0;
    }
    else
    {
        ray->wall_x = v.x;
        ray->wall_y = v.y;
        ray->distance = v.dist;
        ray->hit_vertical = 1;
    }
}

/* ------------------------------------------------------------ */
/*   TEXTURE SELECTION                                           */
/* ------------------------------------------------------------ */

static int  select_texture(t_ray *ray)
{
    float   rad;

    rad = deg_to_rad(ray->ray_angle);
    if (ray->hit_vertical)
        return (cos(rad) > 0 ? EA : WE);
    return (sin(rad) > 0 ? SO : NO);
}

/* ------------------------------------------------------------ */
/*   TEXTURE COORDS                                              */
/* ------------------------------------------------------------ */

static int  get_tex_x(t_ray *ray, t_mlx *mlx, int id)
{
    float   offset;
    int     x;

    if (ray->hit_vertical)
        offset = ray->wall_y - floor(ray->wall_y);
    else
        offset = ray->wall_x - floor(ray->wall_x);
    x = (int)(offset * mlx->tex_width[id]);
    if (x < 0)
        x = 0;
    if (x >= mlx->tex_width[id])
        x = mlx->tex_width[id] - 1;
    return (x);
}

static int  get_tex_y(int y, int start, int end, int tex_h)
{
    float   pos;
    int     ty;

    pos = (float)(y - start) / (float)(end - start);
    ty = (int)(pos * tex_h);
    if (ty < 0)
        ty = 0;
    if (ty >= tex_h)
        ty = tex_h - 1;
    return (ty);
}

/* ------------------------------------------------------------ */
/*   DRAW WALL COLUMN                                            */
/* ------------------------------------------------------------ */

static void draw_wall_column(t_mlx *mlx, int col, t_ray *ray)
{
    float   corrected;
    float   h;
    int     start;
    int     end;
    int     id;
    int     tex_x;
    int     y;
    int     tex_y;
    int     color;

    corrected = ray->distance * cosf(deg_to_rad(
                ray->ray_angle - mlx->plyr_angle));
    if (corrected < 0.1f)
        corrected = 0.1f;
    h = 720.0f / corrected;
    start = 360 - h / 2;
    if (start < 0)
        start = 0;
    end = 360 + h / 2;
    if (end > 720)
        end = 720;
    id = select_texture(ray);
    tex_x = get_tex_x(ray, mlx, id);
    y = start;
    while (y < end)
    {
        tex_y = get_tex_y(y, start, end, mlx->tex_height[id]);
        color = mlx->texture_data[id][tex_y * mlx->tex_width[id] + tex_x];
        put_pixel(mlx, col, y, color);
        y++;
    }
}

/* ------------------------------------------------------------ */
/*   MAIN RAY LOOP                                               */
/* ------------------------------------------------------------ */

void    rays(t_map *map, t_mlx *mlx)
{
    int     col;
    t_ray   ray;

    col = 0;
    while (col < 1080)
    {
        ft_bzero(&ray, sizeof(t_ray));
        cast_single_ray(map, mlx, col, &ray);
        draw_wall_column(mlx, col, &ray);
        col++;
    }
}