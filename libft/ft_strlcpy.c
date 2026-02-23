/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonamart <jonamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:13:14 by paulgonz          #+#    #+#             */
/*   Updated: 2026/02/19 18:24:45 by jonamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;
	int		lensrc;

	i = 0;
	lensrc = ft_strlen(src);
	if (n == 0)
		return (lensrc);
	while (src[i] && i < (n - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (lensrc);
}

// int main()
// {
// 	char dst[10] = "jote";
// 	char src[] = "hola que tal";
// 	printf("%d\n", ft_strlcpy(dst, src, 3));
// 	// printf("%zu", strlcpy(dst, src , 3));
// }
