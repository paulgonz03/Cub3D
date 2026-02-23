/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:25:32 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:54:37 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *src, int c)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (src[i] == (char)c)
			return ((char *)src + i);
		i++;
	}
	if (src[i] == (char)c)
		return ((char *)src + i);
	return (NULL);
}

// int	main(void)
// {
// 	char src[] = "Hola que tal";
// 	int c = 'a';
// 	printf("%s\n", ft_strchr(src, c));
// 	printf("%s", strchr(src, c));
// }
