/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      ::::::   */
/*   gnl_node.c                                         :+:      :+:    :+:   */
/*                                                  +:+ +:+           +:+     */
/*   By: yiyuli <yy@eyuan.me>                     +#+  +:+         +#+        */
/*                                              +#+#+#+#+#+      +#+          */
/*   Created: 2025/08/13 14:07:04 by yiyuli           #+#      #+#            */
/*   Updated: 2025/08/13 14:07:06 by yiyuli         ###      ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <bsq.h>

t_gnl_node	*find_or_create_node(t_gnl_node **head, int fd)
{
	t_gnl_node	*current;
	t_gnl_node	*new_node;

	current = *head;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	new_node = malloc(sizeof(t_gnl_node));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->buffer = ft_strdup("");
	if (!new_node->buffer)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

void	remove_node(t_gnl_node **head, int fd)
{
	t_gnl_node	*current;
	t_gnl_node	*temp;

	current = *head;
	if (current && current->fd == fd)
	{
		*head = current->next;
		free(current->buffer);
		free(current);
		return ;
	}
	while (current && current->next)
	{
		if (current->next->fd == fd)
		{
			temp = current->next;
			current->next = temp->next;
			free(temp->buffer);
			free(temp);
			return ;
		}
		current = current->next;
	}
}
