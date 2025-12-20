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

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

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

typedef struct s_parse_flags
{
    int no;
    int pos_no;
    int so;
    int pos_so;
    int we;
    int pos_we;
    int ea;
    int pos_ea;
    int f;
    int pos_f;
    int c;
    int pos_c;
} t_parse_flags;

typedef struct s_files
{
    char *no_file;
    char *so_file;
    char *we_file;
    char *ea_file;
    char *f_file;
    char *c_file;
} t_files;

typedef struct s_mlx
{
    void *mlx;
    void *win;
    void *image[5];
    int img_width;
    int img_height;

} t_mlx;

typedef struct s_map
{
    char **map;
    char *temp;
    int lines;
    int x;
    int y;
    int x_limit;
    int y_limit;
    char type;
    t_files *files;
    t_mlx *mlx_data;
} t_map;

// RAYCAST

// Raycast.c
int raycast(t_map *map_data);

// MAIN.C
void printmap(char **map);

//FREE.C
int error(t_map *map_data, char *mes);
void free_files(t_files *files);
void free_mlx(t_mlx *mlx);
void free_mapdata(t_map *map_data);

// GNL

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

// PARSER.C

// Aux_coordinates.c
int check_order(t_parse_flags *flags);
int realloc_coordinates(t_map *map_data, t_parse_flags *flags);

// Coordinates.c
void find_coordinates(t_map *map_data, t_parse_flags *flags);
int check_flags(t_parse_flags *flags);
int fill_coordinates(t_map *map_data, t_parse_flags *flags);
int coordinates_parser(t_map *map_data);

// Flood_fill.c
void find_player(t_map *map_data);
void limits_map(t_map *map_data);
int aux_flood_fill(t_map *map_data, int x, int y, char **map);
int flood_fill(t_map *map_data);

// Parser.c
int name_map_parser(char **argv);
int parser(t_map *map_data);

// Utils_parser.c
void ft_free_free(char **temp);
int realloc_map(t_map *map_data, int pos);

#endif