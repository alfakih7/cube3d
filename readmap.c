#include "./Includes/cub3d.h"
int surrounded_by_walls(t_vars *vars)
{
	int i = -1;
	int j = -1;
	while (++i < vars->map_height)
	{
		j = -1;
		while (++j < (int)ft_strlen(vars->map[i]))
		{
			if ((i == 0 || i == vars->map_height - 1) && (vars->map[i][j] != '1' && vars->map[i][j] != ' '))
				return (1);
			else if ((j == 0 || j == (int)ft_strlen(vars->map[i])) && (vars->map[i][j] != '1' && vars->map[i][j] != ' '))
				return (1);
		}
	}
	return(0);
}

int filling_map(t_vars *vars, char *line, int fd)
{
	int i = 0;
	int flag = 1;
	while (line)
	{
		if (flag && *line != '\0')
			i++;
		else
			flag = 0;
		free(line);
		line = get_next_line(fd);
		if (!flag && line && *line != '\0')
			return(free_double(NULL, line), 1);
	}
	if (i == 0)
		return (1);
	vars->map = malloc((i + 1) * sizeof(char *));
	if (!vars->map)
		return (1);
	close(fd);
	fd = open(vars->map_name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (check_map_start(line) == 1)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (line)
	{
		if (*line == '\0')
			break ;
		vars->map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	vars->map_height = i;
	vars->map[i] = NULL;
	return (0);
	// printf("map_height = %d\n", vars->map_height);
}

int read_map(t_vars *vars, char *file)
{
	int fd;
	int flag[6];
	char *line;
	int flag_f = 0;
	char **str;
	int counter = 0;

	init_flags(flag);
	line = NULL;
	str = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		(write(2, "Failed to open file\n", 20), exit(1));
	line = get_next_line(fd);
	while (line)
	{
		counter++;
		if (check_map_start(line) == 1)
		{
			free_double(str, NULL);
			flag_f = 1;
			break ;
		}
		free_double(str, NULL);
		str = ft_split(line, ' ');
		if (str && str[0] && ft_strncmp(str[0], "NO", 3) == 0)
			vars->no = ft_strdup(str_after_space(line)), flag[0] += 1;
		else if (str && str[0] && ft_strncmp(str[0], "SO", 3) == 0)
			vars->so = ft_strdup(str_after_space(line)), flag[1] += 1;
		else if (str && str[0] && ft_strncmp(str[0], "WE", 3) == 0)
			vars->we = ft_strdup(str_after_space(line)), flag[2] += 1;
		else if (str && str[0] && ft_strncmp(str[0], "EA", 3) == 0)
			vars->ea = ft_strdup(str_after_space(line)), flag[3] += 1;
		else if (str && str[0] && ft_strncmp(str[0], "F", 2) == 0)
		{
			flag[4] += 1;
			if (parse_floor(vars, line) == 1)
				return(free_double(str, line), 3);
		}
		else if (str && str[0] && ft_strncmp(str[0], "C", 2) == 0)
		{
			flag[5] += 1;
			if (parse_ceiling(vars, line) == 1)
				return(free_double(str, line), 4);
		}
		else if (str && str[0])
			return(free_double(str, line), 1);
		free(line);
		line = get_next_line(fd);
	}
	counter = validate_comps(vars);
	if (counter == 1 && flag_f == 1)
		return(free_double(NULL, line), 6);
	else if (counter == 1 && flag_f == 0)
		return(free_double(str, line), 1);
	if (flag[0] != 1 || flag[1] != 1 || flag[2] != 1 || flag[3] != 1 
		|| flag[4] != 1 || flag[5] != 1)
			return(free_double(NULL, line), 1);
	if (filling_map(vars, line, fd) == 1)
		return(3);
	// vars->map_height = i;
	// vars->map[i] = NULL;
	close(fd);
	return (0);
}