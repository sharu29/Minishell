/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-12 12:42:54 by snataraj          #+#    #+#             */
/*   Updated: 2024-06-12 12:42:54 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i] && i < n)
		i++;
	while (src[j] && (i + j + 1) < n)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (n > i)
		dest[i + j] = '\0';
	return (i + ft_strlen(src));
}

/* int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

#include <stdio.h>
#include <string.h>

int	main(void)
{
	char dest[10] = "Hello";
	char src[] = " World";
	printf("\nReturn: %zu", ft_strlcat(dest, src, sizeof(dest)));
	printf("\nDest:%s", dest);
} */