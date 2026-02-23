/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:58:56 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:58:57 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// int	main(void)
// {
// 	int c = 3;
// 	int a = 'L';
// 	int b = 'a';
// 	int d = 10;

// 	printf("%d\n", ft_isdigit(c));
// 	printf("%d\n", ft_isdigit(a));
// 	printf("%d\n", ft_isdigit(b));
// 	printf("%d", ft_isdigit(d));
// }
