/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:01:04 by araout            #+#    #+#             */
/*   Updated: 2021/01/07 14:09:46 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int check_corrupt(void *ptr, void *file, off_t size)
{
	if (ptr < file)
		return (1);
	if ((unsigned char *)ptr > (unsigned char *)file + size)
		return (1);
	return (0);
}
