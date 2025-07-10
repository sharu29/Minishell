/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-12 12:42:10 by snataraj          #+#    #+#             */
/*   Updated: 2024-06-12 12:42:10 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (dest);
	if (src < dest)
	{
		i = n;
		while (i > 0)
		{
			i--;
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[100] = "Learningisfun";
	char *first, *second;
	first = str;
	second = str;
	printf("Original string :%s\n ", str);

	// when overlap happens then it just ignore it
	//ft_memcpy(first + 8, first, 10);
	//printf("memcpy overlap : %s\n ", str);

	// when overlap it start from first position
	ft_memmove(second + 8, first, 10);
	printf("ft_memmove overlap : %s\n ", str);

	memmove(second + 8, first, 10);
	printf("memmove overlap : %s\n ", str);

	return (0);
} */