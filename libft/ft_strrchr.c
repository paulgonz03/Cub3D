/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:28:49 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:55:54 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *src, int c)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	while (i >= 0)
	{
		if (src[i] == (char)c)
			return ((char *)&src[i]);
		i--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char src[] = "Paulahjj";
// 	int c = 'a';
// 	printf("%s\n", ft_strrchr(src, c));
// 	printf("%s", strrchr(src, c));
// }
