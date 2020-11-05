/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 04:32:17 by araout            #+#    #+#             */
/*   Updated: 2020/11/01 20:52:27 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
# define MALLOC_ERR 1
# define ERR_FILE_FORMAT 2
# define ERR_OPEN 3
# define ERR_FSTAT 4
# define ERR_MMAP 5
# define ERR_MUNMAP 6

# define FLAG_P 1
# define FLAG_Q 2
# define FLAG_R 4
# define FLAG_S 8
# define AR_MAGIC 0x72613c21
# define AR_CIGAM 0x213c6172
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

typedef struct							s_nm
{
	uint64_t							n_value;
	uint32_t							n_sect;
	char								*n_strx;
	int									n_type;
	int									n_ext;
}										t_nm;

typedef struct							s_sect
{
	uint32_t							index;
	uint32_t							text;
	uint32_t							data;
	uint32_t							bss;
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
void									print_output(t_nm *nm, int flag);
int										handle_32(char *ptr);
int										symtab_64(t_symtab_command *sym,
		char *ptr, t_list *lst);
void									segment_64(t_load_command *lc);
t_list									*build_lst(t_symtab_command *sym,
		char *strtbl, t_nlist_64 *el);
int										ft_sort_root(t_list **head, int flag);
int										handle_64(char *ptr, off_t size);
int										handle_file(char *filename);
void									print_error(int err, char *f);
int										handle_fat_32(char *ptr, off_t size, char *filename);
int										handle_fat_64(char *ptr, off_t size, char *filename);
uint32_t								swap_uint32(uint32_t x);
uint64_t								swap_uint64(uint64_t x);
int										nm(char *ptr, off_t size, char *filename);
t_nm*									make_node(uint64_t n_value, int n_sect,
		char *n_strx, int type);
int										handle_archive(void *ptr, off_t size,
		char *filename);
#endif
