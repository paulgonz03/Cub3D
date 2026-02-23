/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:59:03 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:59:04 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

// int	main(void)
// {
// 	int a = 'a';
// 	int b = 0;
// 	int c = '7';

// 	printf("%d\n", ft_isprint(a));
// 	printf("%d\n", ft_isprint(b));
// 	printf("%d", ft_isprint(c));
// }
