/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonamart <jonamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:25:24 by paulgonz          #+#    #+#             */
/*   Updated: 2026/02/19 18:25:05 by jonamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	int		lensrc;
	size_t	lendst;

	i = 0;
	j = 0;
	lensrc = ft_strlen(src);
	while (dst[j] && j < size)
		j++;
	lendst = j;
	if (size == 0 || size <= lendst)
		return (lensrc + size);
	while (src[i] && i < size - lendst - 1)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (lensrc + lendst);
}

// int	main(void)
// {
// 	// char *dst = NULL;
// 	// char src[] = "hola";
// 	char *dst1 = NULL;
// 	char src1[] = "hola";

// 	// printf("%ld\n", ft_strlcat(dst, src, 4));
// 	printf("%ld\n", strlcat(dst1, src1, 4));
// 	// printf("%s\n", dst);
// 	printf("%s", dst1);
// }
