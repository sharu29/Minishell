/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-13 15:54:26 by snataraj          #+#    #+#             */
/*   Updated: 2024-06-13 15:54:26 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*fstr;

	fstr = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!fstr)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		fstr[i] = (*f)(i, s[i]);
		i++;
	}
	fstr[i] = 0;
	return (fstr);
}
