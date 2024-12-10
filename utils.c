#include "Includes/cub3d.h"

int count_lines(char *file)
{
	int fd;
	int i;
	char *line;

	i = 0;
	fd = open(file, O_RDONLY);
	line = NULL;
	if (fd < 0)
		(write(2, "Error opening map\n", 18), exit(1));
	line = get_next_line(fd);
	while (line)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	close(fd);
	return(i);
}
int check_map_start(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}


int validate_characters(t_vars *vars)
{
	int i;
	int j;
	int flag;

	flag = 0;
	i = -1;
	j = -1;
	while (++i < vars->map_height)
	{
		j = -1;
		while (++j < (int)ft_strlen(vars->map[i]))
		{
			if (vars->map[i][j] != '0' && vars->map[i][j] != '1' && vars->map[i][j] != ' ')
			{
				if (check_for_player(vars->map[i][j]))
				{
					vars->player_x = j;
					vars->player_y = i;
					flag++;
				}
				else
					return(1);
			}
		}
	}
	if (flag != 1)
		return(2);
	return(0);
}

int check_for_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int validate_zero(t_vars *vars)
{
	int i;
	int j;

	j = -1;
	i = -1;
	while (++i < vars->map_height)
	{
		j = -1;
		while (++j < (int)ft_strlen(vars->map[i]))
		{
			if (vars->map[i][j] == '0' || check_for_player(vars->map[i][j]))
			{
				if (j >= (int)ft_strlen(vars->map[i + 1]) || j >= (int)ft_strlen(vars->map[i - 1]))
					return(1);
				else if (vars->map[i][j + 1] == ' ' || vars->map[i][j - 1] == ' '
				|| (vars->map[i + 1][j] == ' ' || vars->map[i - 1][j] == ' '))
					return(1);
			}
		}
	}
	return(0);
}
