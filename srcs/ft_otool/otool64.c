/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:03:38 by araout            #+#    #+#             */
/*   Updated: 2021/01/07 14:25:53 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

void		segment_64(t_load_command *lc)
{
	t_segment_command_64	*seg;
	t_section_64			*sect;
	uint16_t					i;

	seg = (struct segment_command_64 *)lc;
	sect = (struct section_64 *)((void*)seg + sizeof(*seg));
	i = -1;
	while (++i < seg->nsects && (sect + i))
	{
		if (!ft_strcmp((sect + i)->sectname, SECT_TEXT)
				&& !ft_strcmp((sect + i)->segname, SEG_TEXT))
			g_sections.text = g_sections.index + 1;
		else if (!ft_strcmp((sect + i)->sectname, SECT_DATA)
				&& !ft_strcmp((sect + i)->segname, SEG_DATA))
			g_sections.data = g_sections.index + 1;
		else if (!ft_strcmp((sect + i)->sectname, SECT_BSS)
				&& !ft_strcmp((sect + i)->segname, SEG_DATA))
			g_sections.bss = g_sections.index + 1;
		g_sections.index++;
	}
}

int handle_64(char *ptr, off_t size)
{
	t_mach_header_64	*header;
	t_load_command		*lc;
	uint64_t			ncmds;

	header = (t_mach_header_64 *)ptr;
	if (header->magic == MH_CIGAM)
		g_sections.swap = 1;
	else
		g_sections.swap = 0;
	if (check_corrupt((void *)header+1, ptr, size))
		return (ERR_FILE_CORRUPT);
	ncmds = SWAPIF(header->ncmds);
	lc = (void *)ptr + sizeof(t_mach_header_64);
	if (check_corrupt((void*)lc+1, ptr, size))
		return (ERR_FILE_CORRUPT);
	while (--ncmds)
	{
		if (check_corrupt((void*)lc+1, ptr, size))
			return (ERR_FILE_CORRUPT);
		lc = (void *)lc + (SWAPIF(lc->cmdsize));
	}	
		return (0);
}
