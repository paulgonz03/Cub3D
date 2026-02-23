/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:54:20 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/11 15:21:54 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(char **p)
{
	int	i;

	i = -1;
	while (p[++i])
		free(p[i]);
	free(p);
}

int	ft_counterwords(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (!s[i])
			return (word);
		while (s[i] != c && s[i] != '\0')
			i++;
		word++;
	}
	return (word);
}

int	ft_counterletters(char *s, char c, int j)
{
	int	i;

	i = 0;
	while (s[j] && s[j] != c)
	{
		j++;
		i++;
	}
	return (i);
}

char	**get_str(char **p, const char *s, char c, int words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (words-- != 0)
	{
		while (s[j] && s[j] == c)
			j++;
		p[i] = ft_calloc(ft_counterletters((char *)s, c, j) + 1, sizeof(char));
		if (!p[i])
			return (free_array(p), NULL);
		k = 0;
		while (s[j] && s[j] != c)
			p[i][k++] = s[j++];
		i++;
	}
	return (p);
}

char	**ft_split(char *s, char c)
{
	char	**p;
	int		words;

	if (s == NULL)
		return (NULL);
	words = ft_counterwords((char *)s, c);
	p = ft_calloc(words + 1, sizeof(char *));
	if (!p)
		return (0);
	return (get_str(p, s, c, words));
}

// int	main(void)
// {
// 	char	s[] = "hola que tal";
// 	char	c;
// 	int		i;
// 	char	**p;

// 	c = ' ';
// 	i = 0;
// 	p = ft_split(s, c);
// 	while (p[i])
// 	{
// 		printf("p->%s\n", p[i]);
// 		i++;
// 	}
// }
