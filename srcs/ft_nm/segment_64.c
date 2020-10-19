/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:42:38 by araout            #+#    #+#             */
/*   Updated: 2020/10/12 18:25:09 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void		segment_64(t_load_command *lc)
{
	t_segment_command_64	*seg;
	t_section_64			*sect;
	int						i;
	int						nseg;

	seg = (struct segment_command_64 *)lc;
	sect = (struct section_64 *)((void*)seg + sizeof(*seg));
	nseg = seg->nsects;
	i = -1;
	while (++i < nseg)
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
}
