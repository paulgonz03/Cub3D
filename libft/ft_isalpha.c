/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:58:44 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 20:58:45 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

// int main()
// {
// 	int c = 'A';
// 	int d = '0';
// 	int e = '(';
// 	printf ("%d\n", ft_isalpha(c));
// 	printf ("%d\n", ft_isalpha(d));
// 	printf ("%d", ft_isalpha(e));

// }
