/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikhaing <0x@bontal.net>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 02:56:12 by mikhaing          #+#    #+#             */
/*   Updated: 2025/08/13 02:56:20 by mikhaing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bsq.h>

char	**read_grid(int fd, t_map_info *info)
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
