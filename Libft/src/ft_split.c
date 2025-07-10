/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-18 14:23:02 by snataraj          #+#    #+#             */
/*   Updated: 2024-06-18 14:23:02 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(char const *s, char c)
{
	int	i;
	int	count;
	int	b;

	count = 0;
	i = 0;
	b = 0;
	while (s[i])
	{
		if (s[i] == c)
			b = 0;
		else if (b == 0)
		{
			b = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*ft_create_word(char const *s, char c)
{
	char	*dt;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	dt = (char *)malloc(sizeof(char) * i + 1);
	if (!dt)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		dt[i] = s[i];
		i++;
	}
	dt[i] = '\0';
	return (dt);
}

static char	**ft_free(char **st, int i)
{
	while (--i)
		free(st[i]);
	free(st);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**fstr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	fstr = (char **)malloc(sizeof(char *) * (ft_words(s, c) + 1));
	if (!fstr)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			fstr[i] = ft_create_word(s, c);
			i++;
			if (fstr[i - 1] == NULL)
				return (ft_free(fstr, i));
			while (*s && *s != c)
				s++;
		}
	}
	fstr[i] = NULL;
	return (fstr);
}

/* #include <stdio.h>

int	main(void)
{
	int			i;
	const char	*str = "Hello,World,Split,Me";
	char		**split_array;

	i = 0;
	split_array = ft_split(str, ',');
	while (split_array[i])
	{
		printf("%s\n", split_array[i]);
		i++;
	}
} */
