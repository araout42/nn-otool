/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:03:38 by araout            #+#    #+#             */
/*   Updated: 2021/01/08 18:26:30 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

void		print_unsigned(size_t addr, size_t base, size_t len)
{
	char	value;

	if (len <= 0)
		return ;
	print_unsigned(addr / base, base, len - 1);
	value = HEX_STRING[(addr % base)];
	write(1, &value, 1);
}


int			print_output_64(void *ptr, off_t size, uint64_t sect_size, uint64_t sect_addr)
{
	size_t i= 0;
	(void)sect_addr;
	if (ptr + size < ptr + sect_size)
	{
		return (ERR_FILE_CORRUPT);
	}
	while (i < sect_size + ((sect_size % 16) ? (16 - sect_size % 16) : 0))
	{
		if (i % 16 == 0)
		{
			print_unsigned(sect_addr + i, 16, 16);
			write(1, "\t", 1);
		}
		if (i < sect_size)
			print_unsigned(0xff & ((char *)ptr)[i], 16, 2);
		if (!g_sections.swap && i < sect_size)
			write(1, " ", 1);
		if (i % 16 == 15)
			write(1, "\n", 1);
		i++;
	}
	return (0);	
}

int			segment_64(t_load_command *lc, void* ptr, off_t size)
{
	t_segment_command_64	*seg;
	t_section_64			*sect;
	int					i;

	seg = (t_segment_command_64 *)lc;
	sect = (t_section_64 *)((void*)seg + sizeof(*seg));
	i = -1;
	while (++i < SWAPIF64(seg->nsects) && !check_corrupt(sect + i, ptr, size))
	{
		if (!ft_strcmp((sect + i)->sectname, SECT_TEXT)
				&& !ft_strcmp((sect + i)->segname, SEG_TEXT))
		{
			if (check_corrupt((void*)ptr + (SWAPIF64(sect[i].offset)), ptr, size))
			{
				return (ERR_FILE_CORRUPT);
			}
			return (print_output_64(ptr + (SWAPIF64((sect[i].offset))), size, SWAPIF64(sect[i].size), SWAPIF64(sect[i].addr)));
		}
	}
	return (0);
}

int handle_64(char *ptr, off_t size)
{
	t_mach_header_64	*header;
	t_load_command		*lc;
	uint64_t			ncmds;
	int					ret;

	header = (t_mach_header_64 *)ptr;
	if (header->magic == MH_CIGAM)
		g_sections.swap = 1;
	else
		g_sections.swap = 0;
	if (check_corrupt((void *)header+1, ptr, size))
		return (ERR_FILE_CORRUPT);
	ncmds = SWAPIF64(header->ncmds);
	lc = (void *)ptr + sizeof(t_mach_header_64);
	if (check_corrupt((void*)lc+1, ptr, size))
		return (ERR_FILE_CORRUPT);
	while (--ncmds)
	{
		if (check_corrupt((void*)lc+1, ptr, size))
			return (ERR_FILE_CORRUPT);
		if (SWAPIF64(lc->cmd) == LC_SEGMENT_64)
		{
			if ((ret = segment_64(lc, ptr, size)) != 0)
				return (ret);
		}

		lc = (void *)lc + (SWAPIF64(lc->cmdsize));
	}	
		return (0);
}
