#include "Includes/cub3d.h"

int array_len(char **str)
{
	int i = 0;
	while (str[i])
		i++;
	return(i);
}

char *str_after_space(char *str)
{
	while (str && *str && *str == ' ')
		str++;
	while (str && *str && *str != ' ')
		str++;
	while (str && *str && *str == ' ')
		str++;
	return (str);
}

int validate_mapex(char *file)
{
	int i = 0;
	while (file[i])
		i++;
	if (!(file[i - 1] == 'u' || file[i - 2] == 'u' 
		|| file[i - 3] == 'c' || file[i - 4] == '.'))
		return (1);
	return (0);
}

void print_map(t_vars *vars)
{
	int i = 0;
	while (vars->map[i])
	{
		printf("%s\n", vars->map[i]);
		i++;
	}
}

int validate_comps(t_vars *vars)
{
	if (!vars->no || !vars->so || !vars->we || !vars->ea)
		return (1);
	return (0);
}


int main(int argc, char **argv)
{
	t_vars vars;
	if (argc != 2)
		return(write(2, "Error\nInvalid Number of Arguments\n", 34));
	if (validate_mapex(argv[1]) == 1)
		return(write(2, "Invalid Map Extension\n", 22));
	initialize_vars(&vars, argv);
	if (all_parsing(&vars) != 0)
		return(free_all(&vars), 1);
	print_comps(&vars);
	printf("\n\n\n");
	print_map(&vars);
}
