/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-12 12:42:27 by snataraj          #+#    #+#             */
/*   Updated: 2024-06-12 12:42:27 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 0)
	{
		while (src[i] != '\0' && i < (n - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	char src[] = "Hello";
	char dest[6];
	printf("\nReturn: %zu",ft_strlcpy(dest, src, sizeof(dest)));
	printf("\nDest:%s", dest);

		char src[] = "This is a very long string";
	char dest[10];
	ft_strlcpy(dest, src, sizeof(dest));
} */