/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:41:03 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:56:00 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, s1[i]))
		i++;
	while (ft_strchr(set, s1[j - 1]))
		j--;
	return (ft_substr(s1, i, j - i));
}

/*int main()
{
	char s1[] = "hola que tal";
	char set[] = "que";
	printf("%s\n", ft_strtrim(s1, set));
}*/
