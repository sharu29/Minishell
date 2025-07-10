/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-13 10:08:53 by snataraj          #+#    #+#             */
/*   Updated: 2024-06-13 10:08:53 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t mem, size_t size)
{
	void	*p;

	if (mem == 0 || size == 0)
	{
		mem = 1;
		size = 1;
	}
	if (mem != 0 && size != 0 && (mem * size) / size != mem)
		return (NULL);
	p = malloc((mem * size));
	if (!p)
		return (NULL);
	else
		ft_bzero(p, (mem * size));
	return (p);
}
