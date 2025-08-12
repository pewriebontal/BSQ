/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikhaing <0x@bontal.net>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:06:13 by mikhaing          #+#    #+#             */
/*   Updated: 2025/08/12 00:50:41 by mikhaing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bsq.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_fr;
	unsigned char	*src_fr;

	if (NULL == src && NULL == dest)
		return (NULL);
	dest_fr = (unsigned char *)dest;
	src_fr = (unsigned char *)src;
	while (n > 0)
	{
		*dest_fr = *src_fr;
		dest_fr++;
		src_fr++;
		n--;
	}
	return (dest);
}
