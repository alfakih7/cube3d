#include "./Includes/cub3d.h"

int count_commas(char *str)
{
	int i = 0;
	int counter = 0;
	while (str[i])
	{
		if (str[i] == ',')
			counter++;
		i++;
	}
	return(counter);
}
int parse_floor(t_vars *vars, char *str)
{
	int i;
	char **comma_split;

	i = 0;
	while (*str == ' ')
		str++;
	str++;
	if (count_commas(str) != 2)
		return (1);
	comma_split = ft_split(str, ',');
	if (array_len(comma_split) != 3)
		return (free_double(comma_split, NULL), 1);
	while (comma_split && comma_split[i])
	{
		vars->floor_color[i] = ft_atoi(comma_split[i]);
		i++;
	}
	if (vars->floor_color[0] == -1 || vars->floor_color[1] == -1 ||
		vars->floor_color[2] == -1)
		return(free_double(comma_split, NULL), 1);
	return(free_double(comma_split, NULL), 0);
}
int parse_ceiling(t_vars *vars, char *str)
{
	int i;
	char **comma_split;

	i = 0;
	while (*str == ' ')
		str++;
	str++;
	if (count_commas(str) != 2)
		return (1);
	comma_split = ft_split(str, ',');
	if (array_len(comma_split) != 3)
		return(free_double(comma_split, NULL), 1);
	while (comma_split && comma_split[i])
	{
		vars->ceiling_colors[i] = ft_atoi(comma_split[i]);
		i++;
	}
	if (vars->ceiling_colors[0] == -1 || vars->ceiling_colors[1] == -1 ||
		vars->ceiling_colors[2] == -1)
		return(free_double(comma_split, NULL), 1);
	return(free_double(comma_split, NULL), 0);
}

int all_parsing(t_vars *vars)
{
	int i;

	i = read_map(vars, vars->map_name);
	if (i == 1)
		return(write(2, "Error\nError With The Component\n", 31));
	else if (i == 2)
		return(write(2, "Error\nError With The Map\n", 25));
	else if (i == 3)
		return(write(2, "Error\nError With The Floor Setting\n", 35));	
	else if (i == 4)
		return(write(2, "Error\nError With The Ceiling Setting\n", 37));
	else if (i == 6)
		return(write(2, "Error\nFile Shouldn't Start With The Map\n", 40));
	if (validate_comps(vars) == 1)
		return(write(2, "Error\nError With The Components\n", 32));
	if (surrounded_by_walls(vars) == 1)
		return(write(2, "Error\nMap Not Surrounded By Walls\n", 34));
	if (validate_zero(vars) == 1)
		return(write(2, "Error\nInvalid Path\n", 19));
	i = validate_characters(vars);
	if (i == 2)
		return(write(2, "Error\nInvalid Character\n", 24));
	else if (i == 1)
		return(write(2, "Error\nInvalid Player Count\n", 27));
	return(0);
}