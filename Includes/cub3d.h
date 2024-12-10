
#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "../libft/libft.h"

typedef struct s_vars {
	char **map;
	char *no;
	char *so;
	char *we;
	char *ea;
	char *map_name;
	int floor_color[3];
	int ceiling_colors[3];
	int map_height;
	int player_x;
	int player_y;
}	t_vars;

int validate_comps(t_vars *vars);
int check_for_player(char c);
void free_double(char **map, char *str);
int all_parsing(t_vars *vars);
void free_all(t_vars *vars);
void initialize_vars(t_vars *vars, char **argv);
int array_len(char **str);
int read_map(t_vars *vars, char *file);
int validate_zero(t_vars *vars);
int surrounded_by_walls(t_vars *vars);
int validate_characters(t_vars *vars);
int check_map_start(char *line);
char *str_after_space(char *str);
int parse_floor(t_vars *vars, char *str);
int parse_ceiling(t_vars *vars, char *str);
void init_flags(int *flag);
void print_comps(t_vars *vars);
#endif