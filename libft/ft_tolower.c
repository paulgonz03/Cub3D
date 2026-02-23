/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:56:08 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:56:09 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

// int main()
// {
// 	int a = '(';
// 	int b = 'a';
// 	int c = 'B';

// 	printf("%c\n", ft_tolower(a));
// 	printf("%c\n", ft_tolower(b));
// 	printf("%c\n", ft_tolower(c));
// 	printf("%c\n", tolower(a));
// 	printf("%c\n", tolower(b));
// 	printf("%c\n", tolower(c));
// }