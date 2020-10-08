/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout </var/mail/araout>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:28:59 by araout            #+#    #+#             */
/*   Updated: 2020/10/08 16:44:43 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	print_three_bytes(unsigned int c, int fd)
{
	unsigned int tmp;

	tmp = 0xE08080 | (c & 0x3F);
	tmp = tmp | ((c & 0xfC0) << 2);
	tmp = tmp | ((c & 0xf000) << 4);
	c = (tmp & 0xFF0000) >> 16;
	write(fd, &c, 1);
	c = (tmp & 0xFF00) >> 8;
	write(fd, &c, 1);
	c = tmp & 0xFF;
	write(fd, &c, 1);
}

void	print_four_bytes(unsigned int c, int fd)
{
	unsigned int tmp;

	tmp = 0xF0808080 | (c & 0x3F);
	tmp = tmp | ((c & 0xfc0) << 2);
	tmp = tmp | ((c & 0x3F000) << 4);
	tmp = tmp | ((c & 0x1C0000) << 6);
	c = (tmp & 0xFF000000) >> 24;
	write(fd, &c, 1);
	c = (tmp & 0xFF0000) >> 16;
	write(fd, &c, 1);
	c = (tmp & 0xFF00) >> 8;
	write(fd, &c, 1);
	c = tmp & 0xFF;
	write(fd, &c, 1);
}

void	ft_putchar_uni(int c)
{
	int tmp;

	if (ft_get_lastbit(c) <= 6)
		write(1, &c, 1);
	else if (ft_get_lastbit(c) <= 10)
	{
		tmp = 0xC080 | (c & 0x3F);
		tmp = tmp | ((c & 0xfC0) << 2);
		c = (tmp & 0xFF00) >> 8;
		write(1, &c, 1);
		c = tmp & 0xFF;
		write(1, &c, 1);
	}
	else if (ft_get_lastbit(c) <= 15)
		print_three_bytes(c, 1);
	else
		print_four_bytes(c, 1);
}

int		ft_putstr_uni(int *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putchar_uni(str[i]);
		i++;
	}
	return (i);
}

int		ft_putnstr_uni(int *str, int len)
{
	int i;

	i = 0;
	while (str[i] && i < len)
	{
		ft_putchar_uni(str[i]);
		i++;
	}
	return (i);
}
