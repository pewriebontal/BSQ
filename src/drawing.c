/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikhaing <0x@bontal.net>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:39:21 by mikhaing          #+#    #+#             */
/*   Updated: 2025/08/13 02:19:57 by mikhaing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	draw_solution(char **grid, t_map_info *info, t_solution *solution)
{
	int	r;
	int	c;
	int	start_row;
	int	start_col;

	if (solution->size == 0)
		return ;
	start_row = solution->row - solution->size + 1;
	start_col = solution->col - solution->size + 1;
	r = start_row;
	while (r <= solution->row)
	{
		c = start_col;
		while (c <= solution->col)
		{
			grid[r][c] = info->full;
			c++;
		}
		r++;
	}
}

void	print_grid(char **grid, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		ft_putstr_fd(grid[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
