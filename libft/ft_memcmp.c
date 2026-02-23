/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:06:34 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:52:42 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (p1[i] != p2[i])
			break ;
		i++;
	}
	if (i >= n)
		return (0);
	return ((unsigned char)p1[i] - (unsigned char)p2[i]);
}

// int main()
// {
// 	char s1[] = "paula";
// 	char s2[] = "paulj";
// 	char s3[] = "paula";
// 	char s4[] = "paulj";
// 	printf("%d\n", ft_memcmp(s1, s2, 5));
// 	printf("%d", memcmp(s3, s4, 5));
// }
