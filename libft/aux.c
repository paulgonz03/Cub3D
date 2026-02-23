/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulgonz <paulgonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:08:02 by paulgonz          #+#    #+#             */
/*   Updated: 2024/10/18 19:07:03 by paulgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_printnbr(int nb)
{
	char	aux;
	int		i;

	i = 0;
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		nb = nb * (-1);
		i += write(1, "-", 1);
	}
	if (nb > 9)
		i += ft_printnbr(nb / 10);
	aux = nb % 10 + 48;
	i += write(1, &aux, 1);
	return (i);
}

int	ft_printunbr(unsigned int nb)
{
	char	aux;
	int		i;

	i = 0;
	if (nb > 9)
		i += ft_printnbr(nb / 10);
	aux = nb % 10 + 48;
	i += write(1, &aux, 1);
	return (i);
}

int	ft_printhex(unsigned long const nb, char c)
{
	int		counter;
	char	*s;

	counter = 0;
	s = "0123456789abcdef";
	if (c == 'X')
		s = "0123456789ABCDEF";
	if (c == 'p')
	{
		if (!nb)
		{
			counter += write(1, "(nil)", 5);
			return (counter);
		}
		counter = ft_printstr("0x");
		c = 'x';
	}
	if (nb < 16)
		return (counter += ft_printchar(s[nb]));
	counter += ft_printhex(nb / 16, c);
	counter += ft_printhex(nb % 16, c);
	return (counter);
}
