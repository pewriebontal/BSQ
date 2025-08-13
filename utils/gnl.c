/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      ::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                  +:+ +:+           +:+     */
/*   By: yiyuli <yy@eyuan.me>                     +#+  +:+         +#+        */
/*                                              +#+#+#+#+#+      +#+          */
/*   Created: 2025/08/13 14:05:56 by yiyuli           #+#      #+#            */
/*   Updated: 2025/08/13 14:07:29 by yiyuli         ###      ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <bsq.h>

static int	read_to_buffer(t_gnl_node *node)
{
	char	*read_buf;
	char	*temp;
	int		bytes_read;

	read_buf = malloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	if (!read_buf)
		return (0);
	bytes_read = 1;
	while (!ft_strchr(node->buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(node->fd, read_buf, GNL_BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(read_buf);
			return (0);
		}
		read_buf[bytes_read] = '\0';
		temp = ft_strjoin(node->buffer, read_buf);
		free(node->buffer);
		node->buffer = temp;
	}
	free(read_buf);
	return (1);
}

static char	*extract_and_update(t_gnl_node *node)
{
	char	*line;
	char	*temp;
	int		line_len;

	if (!node->buffer || node->buffer[0] == '\0')
		return (NULL);
	line_len = 0;
	while (node->buffer[line_len] && node->buffer[line_len] != '\n')
		line_len++;
	if (node->buffer[line_len] == '\n')
		line_len++;
	line = ft_substr(node->buffer, 0, line_len);
	temp = ft_substr(node->buffer, line_len, ft_strlen(node->buffer)
			- line_len);
	free(node->buffer);
	node->buffer = temp;
	return (line);
}

static char	*process_and_cleanup(t_gnl_node **head, int fd)
{
	t_gnl_node	*node;
	char		*line;

	node = find_or_create_node(head, fd);
	if (!node)
		return (NULL);
	if (!read_to_buffer(node))
	{
		remove_node(head, fd);
		return (NULL);
	}
	line = extract_and_update(node);
	if (!line || !*line)
	{
		remove_node(head, fd);
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl_node	*head = NULL;

	if (fd < 0 || GNL_BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (fd >= 0)
			remove_node(&head, fd);
		return (NULL);
	}
	return (process_and_cleanup(&head, fd));
}
