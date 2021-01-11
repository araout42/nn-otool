/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:42:35 by araout            #+#    #+#             */
/*   Updated: 2021/01/11 16:54:29 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

int			print_output_32(void *ptr, off_t m_size, uint64_t size, uint64_t start)
{
	size_t	i;

	i = 0;
	if (ptr + m_size < ptr + size)
		return (ERR_FILE_CORRUPT);
	while (i < size + ((size % 16) ? (16 - size % 16) : 0))
	{
		if (i % 16 == 0)
		{
			print_unsigned(start + i, 16, 8);
			write(1, "\t", 1);
		}
		if (i < size)
			print_unsigned(0xff & ((char *)ptr)[i], 16, 2);
		if (!g_sections.swap && i < size)
			write(1, " ", 1);
		if (g_sections.swap && (i % 4 == 3) && i < size)
			write(1, " ", 1);
		if (i % 16 == 15)
			write(1, "\n", 1);
		i++;
	}
	return(0);
}

int			segment_32(t_load_command *lc, void* ptr, off_t size)
{
	t_segment_command	*seg;
	t_section			*sect;
	int					i;

	seg = (t_segment_command *)lc;
	sect = (t_section *)((void*)seg + sizeof(*seg));
	i = -1;
	while (++i < SWAPIF(seg->nsects) && !check_corrupt(sect + i, ptr, size))
	{
		if (!ft_strcmp((sect + i)->sectname, SECT_TEXT)
				&& !ft_strcmp((sect + i)->segname, SEG_TEXT))
		{
			if (check_corrupt((void*)ptr + (SWAPIF(sect[i].offset)), ptr, size))
			{
				return (ERR_FILE_CORRUPT);
			}
			return (print_output_32(ptr + (SWAPIF((sect[i].offset))), size, SWAPIF(sect[i].size), SWAPIF(sect[i].addr)));
		}
	}
	return (0);
}

int handle_32(char *ptr, off_t size)
{
	t_mach_header	*header;
	t_load_command		*lc;
	uint64_t			ncmds;
	int					ret;

	header = (t_mach_header *)ptr;
	if (header->magic == MH_CIGAM)
		g_sections.swap = 1;
	else
		g_sections.swap = 0;
	if (check_corrupt((void *)header+1, ptr, size))
		return (ERR_FILE_CORRUPT);
	ncmds = SWAPIF(header->ncmds);
	lc = (void *)ptr + sizeof(t_mach_header);
	if (check_corrupt((void*)lc+1, ptr, size))
		return (ERR_FILE_CORRUPT);
	while (--ncmds)
	{
		if (check_corrupt((void*)lc+1, ptr, size))
			return (ERR_FILE_CORRUPT);
		if (SWAPIF(lc->cmd) == LC_SEGMENT)
		{
			if ((ret = segment_32(lc, ptr, size)) != 0)
				return (ret);
		}

		lc = (void *)lc + (SWAPIF(lc->cmdsize));
	}	
		return (0);
	return (0);
}
