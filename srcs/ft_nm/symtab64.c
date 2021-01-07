/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:43:55 by araout            #+#    #+#             */
/*   Updated: 2021/01/07 15:17:27 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int				symtab_64(t_symtab_command *sym, char *ptr, t_list *lst, off_t size)
{
	char			*strtable;
	t_nm			*nm;
	t_list			*lst_begin;
	t_nlist_64		*el;

	
	if (check_corrupt((void*)(sym+1), ptr, size))
		return (ERR_FILE_CORRUPT);
	el = (void *)ptr + (SWAPIF(sym->symoff));
	strtable = (void* )ptr + (SWAPIF(sym->stroff));
	if (check_corrupt((void*)(sym+1), ptr, size))
		return (ERR_FILE_CORRUPT);
	if (check_corrupt((void*)strtable+1, ptr, size))
		return (ERR_FILE_CORRUPT);
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
	if (check_corrupt((void*)header+1, ptr, size))
		return (ERR_FILE_CORRUPT);
	ncmds = SWAPIF(header->ncmds);
	lc = (void *)ptr + sizeof(t_mach_header_64);
	if (check_corrupt((void*)lc+1, ptr, size))
		return (ERR_FILE_CORRUPT);
	offset = sizeof(t_mach_header_64);
	while (ncmds--)
	{
		if (check_corrupt((void*)lc+1, ptr, size))
			return (ERR_FILE_CORRUPT);
		if (lc && lc->cmd == LC_SEGMENT_64)
			segment_64(lc);
		if (lc && lc->cmd == LC_SYMTAB)
			symtab_64((t_symtab_command *)lc, ptr, NULL, size);
		lc = (void *)lc + lc->cmdsize;
	}
	return (0);
}
