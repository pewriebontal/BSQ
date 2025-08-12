/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikhaing <0x@bontal.net>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:39:36 by mikhaing          #+#    #+#             */
/*   Updated: 2025/08/13 02:38:18 by mikhaing         ###   ########.fr       */
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

static void	calculate_cell(int **cache, char **grid, t_map_info *info,
		t_point *p)
{
	if (grid[p->r][p->c] == info->obstacle)
		cache[p->r][p->c] = 0;
	else
	{
		if (p->r == 0 || p->c == 0)
			cache[p->r][p->c] = 1;
		else
			cache[p->r][p->c] = 1 + min_three(cache[p->r][p->c - 1], cache[p->r
					- 1][p->c], cache[p->r - 1][p->c - 1]);
	}
}

void	find_biggest_square(char **grid, t_map_info *info, t_solution *sol)
{
	int		**cache;
	t_point	p;

	sol->size = 0;
	sol->row = 0;
	sol->col = 0;
	cache = create_cache(info->height, info->width);
	if (!cache)
		return ;
	p.r = 0;
	while (p.r < info->height)
	{
		p.c = 0;
		while (p.c < info->width)
		{
			calculate_cell(cache, grid, info, &p);
			check_and_record(sol, cache[p.r][p.c], p.r, p.c);
			p.c++;
		}
		p.r++;
	}
	free_cache(cache, info->height);
}
