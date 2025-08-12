/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikhaing <0x@bontal.net>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:37:47 by mikhaing          #+#    #+#             */
/*   Updated: 2025/08/13 02:57:54 by mikhaing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 69
# endif

typedef struct s_map_info
{
	int		height;
	int		width;
	char	empty;
	char	obstacle;
	char	full;
}			t_map_info;

typedef struct s_solution
{
	int		row;
	int		col;
	int		size;
}			t_solution;

typedef struct s_point
{
	int		r;
	int		c;
}			t_point;

void		solve_map_from_file(int fd);
int			read_and_validate_map(int fd, t_map_info *info, char ***grid_addr);
char		**read_grid(int fd, t_map_info *info);
void		find_biggest_square(char **grid, t_map_info *info, t_solution *sol);
void		draw_solution(char **grid, t_map_info *info, t_solution *solution);
void		print_grid(char **grid, int height);
void		free_grid(char **grid, int height);
void		free_cache(int **cache, int height);
int			**create_cache(int height, int width);

long		ft_atol(char *str);
int			ft_atoi(char *str);
int			ft_isnumeric(const char *str);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(char const *src);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char		*ft_strloc(size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*get_next_line(int fd);

#endif