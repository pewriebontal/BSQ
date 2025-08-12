/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikhaing <0x@bontal.net>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:39:28 by mikhaing          #+#    #+#             */
/*   Updated: 2025/08/13 02:26:58 by mikhaing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bsq.h>

static int	parse_first_line(char *line, t_map_info *info)
{
	int	len;

	len = ft_strlen(line);
	if (len < 4)
		return (0);
	info->full = line[len - 1];
	info->obstacle = line[len - 2];
	info->empty = line[len - 3];
	line[len - 3] = '\0';
	if (!(ft_isprint(info->empty) && ft_isprint(info->obstacle)
			&& ft_isprint(info->full)))
		return (0);
	if (info->empty == info->obstacle || info->empty == info->full
		|| info->obstacle == info->full)
		return (0);
	if (!ft_isnumeric(line) || ft_atoi(line) <= 0)
		return (0);
	info->height = ft_atoi(line);
	return (1);
}

static char	**read_grid(int fd, t_map_info *info)
{
	char	**grid;
	int		i;
	char	*line;

	grid = malloc(sizeof(char *) * (info->height));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < info->height)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free_grid(grid, i);
			return (NULL);
		}
		grid[i] = line;
		i++;
	}
	return (grid);
}

static int	validate_grid_content(char **grid, t_map_info *info)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(grid[0]);
	if (grid[0][len - 1] == '\n')
		grid[0][len - 1] = '\0';
	info->width = ft_strlen(grid[0]);
	if (info->width == 0)
		return (0);
	i = 0;
	while (i < info->height)
	{
		len = ft_strlen(grid[i]);
		if (grid[i][len - 1] == '\n')
			grid[i][len - 1] = '\0';
		if ((int)ft_strlen(grid[i]) != info->width)
			return (0);
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] != info->empty && grid[i][j] != info->obstacle)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	read_and_validate_map(int fd, t_map_info *info, char ***grid_addr)
{
	char	*first_line;
	char	*extra_line;

	first_line = get_next_line(fd);
	if (!first_line)
		return (0);
	if (first_line[ft_strlen(first_line) - 1] == '\n')
		first_line[ft_strlen(first_line) - 1] = '\0';
	if (!parse_first_line(first_line, info))
	{
		free(first_line);
		return (0);
	}
	free(first_line);
	*grid_addr = read_grid(fd, info);
	if (!(*grid_addr))
		return (0);
	extra_line = get_next_line(fd);
	if (extra_line != NULL)
	{
		free(extra_line);
		free_grid(*grid_addr, info->height);
		return (0);
	}
	if (!validate_grid_content(*grid_addr, info))
	{
		free_grid(*grid_addr, info->height);
		return (0);
	}
	return (1);
}
