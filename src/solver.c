/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikhaing <0x@bontal.net>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:39:36 by mikhaing          #+#    #+#             */
/*   Updated: 2025/08/13 02:20:07 by mikhaing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bsq.h>

static int	min_three(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	return (c);
}

static void	check_and_record(t_solution *sol, int val, int r, int c)
{
	if (val > sol->size)
	{
		sol->size = val;
		sol->row = r;
		sol->col = c;
	}
}

static void	calculate_cell(int **cache, char **grid, t_map_info *info, int r,
		int c)
{
	if (grid[r][c] == info->obstacle)
		cache[r][c] = 0;
	else
	{
		if (r == 0 || c == 0)
			cache[r][c] = 1;
		else
			cache[r][c] = 1 + min_three(cache[r][c - 1], cache[r - 1][c],
					cache[r - 1][c - 1]);
	}
}

void	find_biggest_square(char **grid, t_map_info *info, t_solution *sol)
{
	int	**cache;
	int	r;
	int	c;

	sol->size = 0;
	sol->row = 0;
	sol->col = 0;
	cache = create_cache(info->height, info->width);
	if (!cache)
		return ;
	r = 0;
	while (r < info->height)
	{
		c = 0;
		while (c < info->width)
		{
			calculate_cell(cache, grid, info, r, c);
			check_and_record(sol, cache[r][c], r, c);
			c++;
		}
		r++;
	}
	free_cache(cache, info->height);
}
