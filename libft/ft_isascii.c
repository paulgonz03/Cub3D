/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:58:53 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 21:15:47 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

// int	main(void)
// {
// 	int a = 'a';
// 	int b = '7';
// 	int c = ')';

// 	printf("%d\n", ft_ascii(a));
// 	printf("%d\n", ft_ascii(b));
// 	printf("%d", ft_ascii(c));
// }
