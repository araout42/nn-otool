/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout </var/mail/araout>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:48:30 by araout            #+#    #+#             */
/*   Updated: 2020/10/08 16:48:36 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

size_t		ft_putnstr_fd(char *str, size_t n, int fd)
{
	size_t i;

	if (str == NULL)
		return (ft_putnstr_fd("(null)", n, fd));
	i = 0;
	while (str[i] && i < n)
		i++;
	write(fd, str, i);
	return (i);
}
