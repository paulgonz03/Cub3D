/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:08:57 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:56:04 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	i;
	size_t			j;
	unsigned int	lenstr;

	j = 0;
	i = start;
	lenstr = ft_strlen(s);
	if (!s)
		return (0);
	if (start >= lenstr)
		return (ft_strdup(""));
	if (lenstr - start < len)
		len = (lenstr - start);
	p = ft_calloc((len + 1), sizeof(char));
	if (!p)
		return (0);
	while (s[i] && j < len)
		p[j++] = s[i++];
	return (p);
}

// int main()
// {
// 	char s[] = "hola que tal";
// 	unsigned int start = 5;
// 	printf("%s", ft_substr(s, start, 7));
// }
