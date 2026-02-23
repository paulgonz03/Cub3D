/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:01:56 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:52:52 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int					i;
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	i = 0;
	if (d == NULL && s == NULL)
		return (0);
	if (d <= s)
		ft_memcpy(dest, src, n);
	else
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			d[i] = s[i];
			i--;
		}
	}
	return (d);
}

// int main()
// {
// 	char *src = "adios";
// 	char *dest = "hola que tal";
// 	// printf("A: %p\n", ft_memmove(dest, src, 7));
// 	printf("B: %p\n", memmove(dest, src, 7));
// }
