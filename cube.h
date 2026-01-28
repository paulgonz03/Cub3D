#ifndef CUBE_H
#define CUBE_H

#include "./libft/libft.h"
#include "minilibx-linux/mlx.h"
#include <fcntl.h>
#include <limits.h>
#include <strings.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#define MINIMAP_SIZE 12
#define TILE_SIZE 15
#define MINIMAP_OFFSET 20

#define KEYA 97
#define KEYS 115
#define KEYD 100
#define KEYW 119
#define KEYUP 65362
#define KEYRIGHT 65363
#define KEYDOWN 65364
#define KEYLEFT 65361
#define KEYESC 65307
#define CLOSEWIN 17

enum
{
    NO = 0,
    SO,
    WE,
    EA,
    TOTAL
};

typedef struct s_files
{
    char *no_file;
    char *so_file;
    char *we_file;
    char *ea_file;
    char *f_file;
    char *c_file;
    int f_col_r;
    int f_col_g;
    int f_col_b;
    int c_col_r;
    int c_col_g;
    int c_col_b;
} t_files;

typedef struct s_keys
{
    int w;
    int a;
    int s;
    int d;
    int left;
    int right;
} t_keys;

typedef struct s_minimap
{
    void *wall_img;
    void *floor_img;
    void *player_img;
    void *void_img;
    int img_width;
    int img_height;

} t_minimap;

typedef struct s_mlx
{
    void *mlx;
    void *win;
    void *image[5];
    void *img;
    char *img_data;
    int *texture_data[5];
    int bpp;         // bits per pixel
    int bpl;         // bits per line
    int order_bytes; // orden de bytes
    int img_width;
    int img_height;
    int plyr_angle;
    int mouse;
    t_minimap *mini_map;
    t_keys *keys;
} t_mlx;

typedef struct s_map
{
    char **map;
    int lines;
    float x_plyr;
    float y_plyr;
    int x_limit;
    int y_limit;
    char view_player;
    char type;
    t_files *files;
    t_mlx *mlx_data;
} t_map;


//##################################################
//##                  BONUS                       ##
//##################################################

// Minimap.c
int mini_map(t_map *map_data, t_minimap *mini_map);

//##################################################
//##                 RAYCAST                      ##
//##################################################

// Raycast.c
void init_data(t_map *map_data);
int	check_walls(t_mlx *mlx_data, float y, float x, t_map *map_data);
int game_loop(void *data);
int raycast(t_map *map_data);

// Keys.c
int closewin(t_mlx *mlx_data);
int key_press(int keycode, t_mlx *mlx_data);
int key_release(int keycode, t_mlx *mlx_data);
void key_moves(t_map *map_data, t_mlx *mlx_data);
int mouse(int x, int y, t_mlx *mlx_data);

//Textures.c
void paint_background(t_map *map_data, t_mlx *mlx_data);
int init_textures(t_files *files, t_mlx *mlx_data);


//##################################################
//##                   CUBE                       ##
//##################################################
void printmap(char **map);

//##################################################
//##                   FREE                       ##
//##################################################
int error(t_map *map_data, char *mes);
void free_files(t_files *files);
void free_mlx(t_mlx *mlx);
void free_mapdata(t_map *map_data);

//##################################################
//##                    GNL                       ##
//##################################################

// Get_next_line_utils.c
int mystrlen(char *str);
char *mystrjoin(char *statica, char *aux_read);
int mystrchr(const char *src, int c);
char *aux_get_read(int fd, char *statica, char *aux_read);

// Get_next_line.c
char *extract_line(char *aux_read);
char *remove_first_line(char *statica);
char *get_read(int fd, char *statica);
char *get_next_line(int fd);

// Map.c
int aux_get_map(char **argv, t_map *data_map);
int get_map(char **argv, t_map *map_data);

//##################################################
//##                  PARSER                      ##
//##################################################

// Coordinates.c
int realloc_map(t_map *map_data, int pos);
int coordinates_parser(t_map *map_data);

// Flood_fill.c
char **copy_map(t_map *map_data);
void find_player(t_map *map_data);
void limits_map(t_map *map_data);
int aux_flood_fill(t_map *map_data, int x, int y, char **map);
int flood_fill(t_map *map_data);

// Parser.c
int parser(t_map *map_data);

// Utils_parser.c
void ft_free_free(char **temp);
int char_not_allow(char **map);
int name_map_parser(char **argv);
void sky_floor(t_map *map_data);

#endif