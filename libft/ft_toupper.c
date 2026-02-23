/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:56:15 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:56:20 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

// int	main(void)
// {
// 	int a = 's';
// 	int b = 'A';
// 	int c = '7';

// 	printf("%c\n", ft_toupper(a));
// 	printf("%c\n", ft_toupper(b));
// 	printf("%c\n", ft_toupper(c));
// 	printf("%c\n", toupper(a));
// 	printf("%c\n", toupper(b));
// 	printf("%c", toupper(c));
// }
