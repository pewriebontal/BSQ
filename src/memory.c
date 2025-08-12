/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikhaing <0x@bontal.net>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:39:33 by mikhaing          #+#    #+#             */
/*   Updated: 2025/08/13 02:20:05 by mikhaing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bsq.h>

void	free_grid(char **grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
	{
		if (grid[i])
			free(grid[i]);
		i++;
	}
	free(grid);
}

void	free_cache(int **cache, int height)
{
	int	i;

	if (!cache)
		return ;
	i = 0;
	while (i < height)
	{
		if (cache[i])
			free(cache[i]);
		i++;
	}
	free(cache);
}

int	**create_cache(int height, int width)
{
	int	**cache;
	int	i;

	cache = malloc(sizeof(int *) * height);
	if (!cache)
		return (NULL);
	i = 0;
	while (i < height)
	{
		cache[i] = malloc(sizeof(int) * width);
		if (!cache[i])
		{
			free_cache(cache, i);
			return (NULL);
		}
		i++;
	}
	return (cache);
}
