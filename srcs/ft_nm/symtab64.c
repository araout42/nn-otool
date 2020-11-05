/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:43:55 by araout            #+#    #+#             */
/*   Updated: 2020/11/01 19:55:37 by araout           ###   ########.fr       */
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
	strtable = ptr + sym->stroff;
	if (!(lst = build_lst(sym, strtable, el)))
		return (-1);
	lst_begin = lst;
	ft_sort_root(&lst_begin, 0);
	lst = lst_begin;
	while (lst)
	{
		nm = (t_nm *)lst->content;
		print_output(nm, 0);
		lst = lst->next;
	}
	return (0);
}

int				handle_64(char *ptr, off_t size)
{
	t_mach_header_64		*header;
	int						ncmds;
	t_load_command			*lc;
	int						i;
	int						offset;

	i = -1;
	(void)size;
	header = (t_mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(t_mach_header_64);
	offset = sizeof(t_mach_header_64);
	while (ncmds--)
	{
		if (lc && lc->cmd == LC_SEGMENT_64)
			segment_64(lc);
		if (lc && lc->cmd == LC_SYMTAB)
			symtab_64((t_symtab_command *)lc, ptr, NULL);
		lc = (void *)lc + lc->cmdsize;
	}
	return (0);
}
