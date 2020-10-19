/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:40:09 by araout            #+#    #+#             */
/*   Updated: 2020/10/19 19:19:02 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int				segment_32(t_load_command *lc)
{
	t_segment_command	*seg;
	t_section			*sect;
	int					i;
	int					nsect;

	seg = (t_segment_command *)lc;
	sect = (t_section *)((void *)seg + sizeof(*seg));
	nsect = seg->nsects;
	i = -1;
	while (++i < nsect)
	{
		if (!ft_strcmp(sect->sectname, SECT_TEXT)
				&& !ft_strcmp(sect->segname, SEG_TEXT))
			g_sections.text = g_sections.index + 1;
		else if (!ft_strcmp(sect->sectname, SECT_DATA)
				&& !ft_strcmp(sect->segname, SEG_DATA))
			g_sections.data = g_sections.index + 1;
		else if (!ft_strcmp(sect->sectname, SECT_BSS)
				&& !ft_strcmp(sect->segname, SEG_DATA))
			g_sections.bss = g_sections.index + 1;
		sect = sect + 1;
		g_sections.index++;
	}
	return (0);
}

t_list*			build_lst_32(t_symtab_command *sym, char *strtbl, t_nlist *el)
{
	t_list			*lst;
	t_list			*lst_begin;
	t_nm			*nm;
	unsigned int	i;

	i = 0;
	while (sym->nsyms > i)
	{
		nm = make_node(el[i].n_value, el[i].n_sect,
				strtbl + el[i].n_un.n_strx, el[i].n_type);
		if (!lst)
		{
			if (!(lst = ft_list_create((char *)nm, sizeof(nm))))
				return (NULL);
			lst_begin = lst;
		}
		else if (!(ft_list_append(&lst_begin, (char *)nm, sizeof(nm))))
			return (NULL);
		i++;
	}
	return (lst_begin);
}

int				symtab_32(t_symtab_command *sym, char *ptr, t_list *lst)
{
	char		*strtable;
	t_nm		*nm;
	t_list		*lst_begin;
	t_nlist		*el;

	el = (void *)ptr + sym->symoff;
	strtable = (void *)ptr + sym->stroff;
	if (!(lst = build_lst_32(sym, strtable, el)))
		return (-1);
	lst_begin = lst;
	ft_sort_root(&lst_begin, 0);
	lst = lst_begin;
	while (lst)
	{
		nm = (t_nm *)lst->content;
		print_output(nm, 32);
		lst = lst->next;
	}
	return (0);
}

int				handle_32(char *ptr)
{
	t_mach_header			*header;
	int						ncmds;
	t_load_command			*lc;
	int						i;

	i = -1;
	header = (t_mach_header *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(t_mach_header);
	while (++i < ncmds)
	{
		if (lc && lc->cmd == LC_SEGMENT)
			segment_32((t_load_command *)lc);
		if (lc && lc->cmd == LC_SYMTAB)
			symtab_32((t_symtab_command *)lc, ptr, NULL);
		lc = (void *)lc + lc->cmdsize;
	}
	return (0);
}
