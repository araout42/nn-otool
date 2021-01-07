/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:07:24 by araout            #+#    #+#             */
/*   Updated: 2021/01/07 14:08:52 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

int check_corrupt(void *ptr, void *file, off_t size)
{
	if (ptr < file)
		return (1);
	if ((unsigned char *)ptr > (unsigned char *)file + size)
		return (1);
	return (0);
}
