/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikhaing <0x@bontal.net>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:39:24 by mikhaing          #+#    #+#             */
/*   Updated: 2025/08/13 02:19:59 by mikhaing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bsq.h>

void	solve_map_from_file(int fd)
{
	char		**grid;
	t_map_info	info;
	t_solution	solution;

	if (read_and_validate_map(fd, &info, &grid))
	{
		find_biggest_square(grid, &info, &solution);
		draw_solution(grid, &info, &solution);
		print_grid(grid, info.height);
		free_grid(grid, info.height);
	}
	else
		ft_putstr_fd("map error\n", 1);
}

int	main(int argc, char **argv)
{
	int	i;
	int	fd;

	if (argc == 1)
		solve_map_from_file(0);
	else
	{
		i = 1;
		while (i < argc)
		{
			fd = open(argv[i], O_RDONLY);
			if (fd == -1)
				ft_putstr_fd("map error\n", 1);
			else
				solve_map_from_file(fd);
			close(fd);
			if (i < argc - 1)
				ft_putchar_fd('\n', 1);
			i++;
		}
	}
	return (0);
}
