/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:43:55 by araout            #+#    #+#             */
/*   Updated: 2020/10/12 17:59:44 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int				symtab_64(t_symtab_command *sym, char *ptr, t_list *lst)
{
	char			*strtable;
	t_nm			*nm;
	t_list			*lst_begin;
	t_nlist_64		*el;

	el = (void *)ptr + sym->symoff;
	strtable = (void *)ptr + sym->stroff;
	if (!(lst = build_lst(sym, strtable, el)))
		return (-1);
	lst_begin = lst;
	ft_sort_root(&lst_begin, 0);
	lst = lst_begin;
	while (lst)
	{
		nm = (t_nm *)lst->content;
		print_output(nm);
		lst = lst->next;
	}
	return (0);
}

int				handle_64(char *ptr)
{
	t_mach_header_64		*header;
	int						ncmds;
	t_load_command			*lc;
	int						i;

	i = -1;
	header = (t_mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(t_mach_header_64);
	while (++i < ncmds)
	{
		if (lc && lc->cmd == LC_SEGMENT_64)
			segment_64((t_load_command *)lc);
		if (lc && lc->cmd == LC_SYMTAB)
			symtab_64((t_symtab_command *)lc, ptr, NULL);
		lc = (void *)lc + lc->cmdsize;
	}
	return (0);
}
