/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 04:33:02 by araout            #+#    #+#             */
/*   Updated: 2021/01/07 14:20:14 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# define MALLOC_ERR 1
# define ERR_FILE_FORMAT 2
# define ERR_OPEN 3
# define ERR_FSTAT 4
# define ERR_MMAP 5
# define ERR_MUNMAP 6
# define ERR_FILE_CORRUPT 7

# define FLAG_P 1
# define FLAG_Q 2
# define FLAG_R 4
# define FLAG_S 8
# define AR_MAGIC 0x72613c21
# define AR_CIGAM 0x213c6172
# define SWAPIF(x) g_sections.swap ? swap_uint32(x) : x
# define SWAPIF64(x) g_sections.swap ? swap_uint64(x) : x
# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <errno.h>
# include "libft.h"
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <ar.h>

typedef struct							s_sect
{
	uint32_t							index;
	uint32_t							text;
	uint32_t							data;
	uint32_t							bss;
	int									swap;
	int									is_set;
}										t_sect;

t_sect									g_sections;

typedef struct nlist_64					t_nlist_64;
typedef struct nlist					t_nlist;
typedef struct section					t_section;
typedef struct section_64				t_section_64;
typedef struct load_command				t_load_command;
typedef struct load_command_64			t_load_command_64;
typedef struct segment_command			t_segment_command;
typedef struct segment_command_64		t_segment_command_64;
typedef struct mach_header				t_mach_header;
typedef struct mach_header_64			t_mach_header_64;
typedef struct symtab_command			t_symtab_command;
typedef struct symtab_command_64		t_symtab_command_64;
typedef struct fat_header				t_fat_header;
typedef struct ar_hdr					t_ar_hdr;


int				handle_file(char *filename);
void			print_error(int err, char *f);
int				handle_64(char *ptr, off_t size);
int				check_corrupt(void *ptr, void *file, off_t size);
uint32_t	swap_uint32(uint32_t x);
uint64_t	swap_uint64(uint64_t x);
#endif
