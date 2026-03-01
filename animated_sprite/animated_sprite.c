#include "cube.h"


void set_torch_normal(t_map *map, t_sprite *sp)
{
    int x = (int)sp->x;
    int y = (int)sp->y;

    if (map->map[y][x+1] == '1') // pared a la derecha
    {
        sp->normal_x = -1;
        sp->normal_y = 0;
    }
    else if (map->map[y][x-1] == '1') // pared a la izquierda
    {
        sp->normal_x = 1;
        sp->normal_y = 0;
    }
    else if (map->map[y+1][x] == '1') // pared abajo
    {
        sp->normal_x = 0;
        sp->normal_y = -1;
    }
    else if (map->map[y-1][x] == '1') // pared arriba
    {
        sp->normal_x = 0;
        sp->normal_y = 1;
    }
}

static int *load_textures(char *path, int *w, int *h, void *mlx)
{
    void    *img;
    int     *data;
    int     *buffer;
    int     bpp;
    int     size_line;
    int     endian;
    int     x;
    int     y;

    img = mlx_xpm_file_to_image(mlx, path, w, h);
    if (!img)
    {
        printf("Error cargando textura: %s\n", path);
        return (NULL);
    }

    data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
    if (!data)
    {
        printf("Error obteniendo data_addr: %s\n", path);
        return (NULL);
    }

    buffer = malloc(sizeof(int) * (*w) * (*h));
    if (!buffer)
        return (NULL);

    for (y = 0; y < *h; y++)
    {
        for (x = 0; x < *w; x++)
        {
            buffer[y * (*w) + x] = data[y * (*w) + x];
        }
    }

    mlx_destroy_image(mlx, img);
    return buffer;
}

void load_fire_sprite(t_mlx *mlx, t_sprite *sp)
{
    sp->frame_count = 4;
    sp->current_frame = 0;
    sp->anim_speed = 0.15f;
    sp->anim_timer = 0;

    sp->frames = malloc(sizeof(int*) * sp->frame_count);
    sp->frame_width = malloc(sizeof(int) * sp->frame_count);
    sp->frame_height = malloc(sizeof(int) * sp->frame_count);

    sp->frames[0] = load_textures("./textures/fire0.xpm", &sp->frame_width[0], &sp->frame_height[0],mlx->mlx);
    sp->frames[1] = load_textures("./textures/fire1.xpm", &sp->frame_width[1], &sp->frame_height[1],mlx->mlx);
    sp->frames[2] = load_textures("./textures/fire2.xpm", &sp->frame_width[2], &sp->frame_height[2],mlx->mlx);
    sp->frames[3] = load_textures("./textures/fire3.xpm", &sp->frame_width[3], &sp->frame_height[3],mlx->mlx);

}
void update_sprite_animation(t_sprite *sp, float dt)
{
    sp->anim_timer += dt;

    if (sp->anim_timer >= sp->anim_speed)
    {
        sp->anim_timer = 0;
        sp->current_frame++;

        if (sp->current_frame >= sp->frame_count)
            sp->current_frame = 0;
    }
}
void draw_sprite(t_mlx *mlx, t_map *map, t_sprite *sp, float *zbuffer)
{
    (void)zbuffer;

    float sx = sp->x - map->x_plyr;
    float sy = sp->y - map->y_plyr;

    float dist = sqrtf(sx*sx + sy*sy);
    if (dist <= 0.1f)
        return;

    float angle = atan2f(sy, sx) * 180.0f / PI;
    float diff = angle - mlx->plyr_angle;

    if (diff < -180) diff += 360;
    if (diff > 180)  diff -= 360;

    int screen_x = (int)((diff + 30.0f) * (WIDTH / 60.0f));

    float size = HEIGHT / dist;

    int draw_start = HEIGHT/2 - size/2;
    if (draw_start < 0) draw_start = 0;
    int draw_end = draw_start + size;
    if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;
    int frame = sp->current_frame;
    int tex_w = sp->frame_width[frame];
    int tex_h = sp->frame_height[frame];
    int *tex = sp->frames[frame];
    if (!tex)
        return;
    for (int x = 0; x < size; x++)
    {
        int col = screen_x + x;
        if (col < 0 || col >= WIDTH)
            continue;

        int tex_x = (x * tex_w) / size;

        for (int y = 0; y < size; y++)
        {
            int row = draw_start + y;
            if (row < 0 || row >= HEIGHT)
                continue;

            int tex_y = (y * tex_h) / size;
            int color = tex[tex_y * tex_w + tex_x];

            if (color != 0xFF00FF)
                put_pixel(mlx, col, row, color);
        }
    }
}




void add_sprite_to_list(t_map *map, t_sprite *sp)
{
    sp->next = NULL;

    if (!map->sprite)
    {
        map->sprite = sp;
        return;
    }

    t_sprite *tmp = map->sprite;
    while (tmp->next)
        tmp = tmp->next;

    tmp->next = sp;
}

void load_torches_from_map(t_map *map, t_mlx *mlx)
{
    int j;
    int i;

    j = 0;
    while (j < map->lines)
    {
        i = 0;
        while (map->map[j][i])   // EXACTAMENTE igual que char_not_allow()
        {
            if (map->map[j][i] == 'T')
            {
                t_sprite *sp = malloc(sizeof(t_sprite));
                if (!sp)
                exit(1);
                
                ft_bzero(sp, sizeof(t_sprite));
                
                sp->x = (float)i ;
                sp->y = (float)j ;
                load_fire_sprite(mlx, sp);
                set_torch_normal(map, sp);
                add_sprite_to_list(map, sp);
                
            }
            i++;
        }
        j++;
    }
}
