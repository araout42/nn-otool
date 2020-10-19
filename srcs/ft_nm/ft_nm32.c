/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:40:09 by araout            #+#    #+#             */
/*   Updated: 2020/10/12 17:51:56 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int				handle_32(char *ptr)
{
	t_mach_header			*header;
	int						ncmds;
	t_load_command			*lc;
	int						i;

	i = 0;
	header = (t_mach_header *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(t_mach_header);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			write(1, "SYMTAB", 6);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (0);
}
