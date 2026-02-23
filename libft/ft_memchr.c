/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:01:28 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:52:36 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
			return (p + i);
		i++;
	}
	return (0);
}

// int main()
// {
// 	char s[] = "paulgonz";
// 	int c = 'g';
// 	char s1[] = "paulgonz";
// 	int c1 = 'g';
// 	printf("%s\n", (char *)ft_memchr(s, c, 6));
// 	printf("%s", (char *)memchr(s1, c1, 6));
// }