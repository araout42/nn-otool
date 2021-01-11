/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_fat32.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:11:30 by araout            #+#    #+#             */
/*   Updated: 2021/01/11 18:07:21 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

static int	is_hostarch(cpu_type_t type)
{
	if ((type == CPU_TYPE_X86_64) && (sizeof(void *) == 8))
		return (1);
	if ((type == CPU_TYPE_I386) && (sizeof(void *) == 4))
		return (1);
	return (0);
}

int			handle_fat_32(char *ptr, off_t size, char *filename)
{
	uint32_t			nfat;
	uint32_t			i;
	struct fat_header	*header;
	struct fat_arch		*arch;
	int					ret;

	(void)filename;
	if (*(unsigned int*)ptr == FAT_CIGAM)
		g_sections.swap = 1;
	else
		g_sections.swap = 0;
	header = (struct fat_header *)ptr;
	nfat = SWAPIF(header->nfat_arch);
	arch = (struct fat_arch *)(header + 1);
	i = -1;
	while (++i < nfat)
	{
		if (check_corrupt((void *)arch + (i * sizeof(struct fat_header)), ptr, size))
			return (ERR_FILE_CORRUPT);
		if (nfat > 1 && !i && is_hostarch(SWAPIF(arch[i + 1].cputype)))
			continue ;
		if ((ret = otool(ptr + (SWAPIF(arch[i].offset)), size, 0)) != 0)
		{
			return (ret);
		}
		if (is_hostarch(swap_uint32(arch[i].cputype)))
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
