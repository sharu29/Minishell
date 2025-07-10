/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-13 10:07:34 by snataraj          #+#    #+#             */
/*   Updated: 2024-06-13 10:07:34 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*s1;
	size_t	i;

	i = 0;
	s1 = (char *)s;
	while (i < n)
	{
		if ((unsigned char)s1[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

/* #include<stdio.h>
int	main(void)
{
	char s[] = {0, 1, 2, 3, 4, 5};

	ft_memchr(s, 0, 0);
	ft_memchr(s, 2, 3);
} */