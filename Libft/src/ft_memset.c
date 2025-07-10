/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-12 12:41:02 by snataraj          #+#    #+#             */
/*   Updated: 2024-06-12 12:41:02 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*d;

	d = (char *)s;
	while (n > 0)
	{
		d[n - 1] = c;
		n--;
	}
	return (s);
}

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[50] = "GeeksForGeeks is for programming geeks.";
	printf("\nBefore memset(): %s\n", str);

	// Fill 8 characters starting from str[13] with '.'
	ft_memset(str + 13, '.', 8*sizeof(char));

	printf("After memset():  %s", str);
	return (0);
}  */
