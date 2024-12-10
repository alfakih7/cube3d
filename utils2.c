#include "Includes/cub3d.h"

void print_comps(t_vars *vars)
{
	printf("NO: (%s)\n", vars->no);
	printf("SO: (%s)\n", vars->so);
	printf("WE: (%s)\n", vars->we);
	printf("EA: (%s)\n", vars->ea);
	printf("Floor: %d %d %d\n", vars->floor_color[0], vars->floor_color[1], vars->floor_color[2]);
	printf("Ceiling: %d %d %d\n", vars->ceiling_colors[0], vars->ceiling_colors[1], vars->ceiling_colors[2]);
}

void init_flags(int *flag)
{
	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	flag[3] = 0;
	flag[4] = 0;
	flag[5] = 0;
}

void initialize_vars(t_vars *vars, char **argv)
{
	vars->map = NULL;
	vars->no = NULL;
	vars->so = NULL;
	vars->we = NULL;
	vars->ea = NULL;
	vars->player_x = -1;
	vars->player_y = -1;
	vars->map_height = 0;
	vars->floor_color[0] = -1;
	vars->floor_color[1] = -1;
	vars->floor_color[2] = -1;
	vars->ceiling_colors[0] = -1;
	vars->ceiling_colors[1] = -1;
	vars->ceiling_colors[2] = -1;
	vars->map_name = argv[1];
}


void free_double(char **map, char *str)
{
	int i;

	i = 0;
	if (str)
	{
		free(str);
		str = NULL;
	}
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void free_all(t_vars *vars)
{
	if (vars->map)
		free_double(vars->map, NULL);
	if (vars->no)
		free(vars->no);
	if (vars->so)
		free(vars->so);
	if (vars->we)
		free(vars->we);
	if (vars->ea)
		free(vars->ea);
	
}

