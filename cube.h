#ifndef CUBE_H
#define CUBE_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <limits.h>
#include <strings.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

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

typedef struct s_map
{
    char **map;
    char *temp;
    int lines;
    t_files *files;
} t_map;

// MAIN
void printmap(char **map);

// GNL
char	*get_next_line(int fd);
char	*extract_line(char *aux_read);
char	*remove_first_line(char *statica);
int		mystrlen(char *str);
char	*mystrjoin(char *statica, char *aux_read);
char	*get_read(int fd, char *statica);
int		mystrchr(const char *src, int c);
char	*aux_get_read(int fd, char *statica, char *aux_read);

//GNL

//Map.c
int aux_get_map(char **argv, t_map *data_map);
int get_map(char **argv, t_map *map_data);

//PARSER.C

//Coordinates.c
void find_coordinates(t_map *map_data, t_parse_flags *flags);
int check_flags(t_parse_flags *flags);
int fill_coordinates(t_map *map_data, t_parse_flags *flags);
int coordinates_parser(t_map *map_data);

//Aux_coordinates.c
int check_order(t_parse_flags *flags);
int newline_parser(t_parse_flags *flags);
int realloc_coordinates(t_map *map_data, t_parse_flags *flags);

//Parser.c
int name_map_parser(char **argv);
int parser(t_map *map_data);

//Utils_parser.c
void ft_free_free(char **temp);
int realloc_map(t_map *map_data, int pos);

#endif