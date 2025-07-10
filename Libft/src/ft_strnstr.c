/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-13 10:08:20 by snataraj          #+#    #+#             */
/*   Updated: 2024-06-13 10:08:20 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*little)
		return ((char *)big);
	if (!big && !len)
		return (NULL);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i] && little[j] && (i + j) < len && big[i + j] == little[j])
			j++;
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

/* #include <stdio.h>

int	main(void)
{
	char str1[] = "Hello, World";
	char str2[] = "World";

	printf("%s", ft_strnstr(str1, str2, sizeof(str1)));
} */