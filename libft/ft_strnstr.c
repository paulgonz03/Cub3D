/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:49 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:55:49 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)big;
	if (little[j] == '\0')
		return (str);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (little[j] != '\0' && big[i + j] == little[j] && i + j < len)
			j++;
		if (little[j] == '\0')
			return (str + i);
		i++;
	}
	return (0);
}

// int main()
// {
// 	char big[] = "MZIRIBMZIRIBMZE123";
// 	char little[] = "MZIRIBMZE";
// 	printf("%s", ft_strnstr(big, little, 10));
// }
