/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:48:31 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/10 21:12:38 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_numb(int fd)
{
	write(fd, "-", 1);
	write(fd, "2", 1);
	write(fd, "1", 1);
	write(fd, "4", 1);
	write(fd, "7", 1);
	write(fd, "4", 1);
	write(fd, "8", 1);
	write(fd, "3", 1);
	write(fd, "6", 1);
	write(fd, "4", 1);
	write(fd, "8", 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	aux;

	if (n == -2147483648)
	{
		ft_numb(fd);
		return ;
	}
	if (n < 0 && n > -2147483648)
	{
		n = n * (-1);
		write(fd, "-", 1);
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	aux = n % 10 + 48;
	write(fd, &aux, 1);
}

// int main()
// {
//     int n = -2147483648;
//     int fd = 2;
//     ft_putnbr_fd(n, fd);
// }