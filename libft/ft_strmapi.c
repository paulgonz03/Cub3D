/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:40:07 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:55:35 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	int		i;

	if (!s || !f)
		return (NULL);
	p = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!p)
		return (NULL);
	i = -1;
	while (s[++i])
		p[i] = f(i, s[i]);
	return (p);
}

// char ft_paulgonz(unsigned int i, char d)
// {
//     char m;
//     i = 1;

//     m = d + i;
//     return(printf("%c", m));
// }

// int main()
// {
//     char s[] = "paula";
//     ft_strmapi(s ,ft_paulgonz);
// }