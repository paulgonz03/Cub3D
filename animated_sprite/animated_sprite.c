#include "cube.h"

void load_fire_sprite(t_mlx *mlx, t_sprite *sp)
{
    sp->frame_count = 4;
    sp->current_frame = 0;
    sp->anim_speed = 0.15f;
    sp->anim_timer = 0;

    sp->frames = malloc(sizeof(int*) * sp->frame_count);
    sp->frame_width = malloc(sizeof(int) * sp->frame_count);
    sp->frame_height = malloc(sizeof(int) * sp->frame_count);

    sp->frames[0] = load_texture("fire_0.xpm", &sp->frame_width[0], &sp->frame_height[0]);
    sp->frames[1] = load_texture("fire_1.xpm", &sp->frame_width[1], &sp->frame_height[1]);
    sp->frames[2] = load_texture("fire_2.xpm", &sp->frame_width[2], &sp->frame_height[2]);
    sp->frames[3] = load_texture("fire_3.xpm", &sp->frame_width[3], &sp->frame_height[3]);

    sp->x = 5.5f;
    sp->y = 5.5f;
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
void draw_sprite(t_mlx *mlx, t_map *map, t_sprite *sp)
{
    float dx = sp->x - map->x_plyr;
    float dy = sp->y - map->y_plyr;
    float dist = sqrtf(dx*dx + dy*dy);

    float angle = atan2f(dy, dx) * 180.0f / PI;
    float diff = angle - mlx->plyr_angle;

    if (diff < -180) diff += 360;
    if (diff > 180) diff -= 360;

    if (fabs(diff) > 60)
        return;

    int screen_x = (int)((diff + 30) * (WIDTH / 60.0f));

    float size = HEIGHT / dist;

    int draw_start = HEIGHT/2 - size/2;
    int draw_end = draw_start + size;

    int frame = sp->current_frame;
    int tex_w = sp->frame_width[frame];
    int tex_h = sp->frame_height[frame];
    int *tex = sp->frames[frame];

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
