/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 04:32:17 by araout            #+#    #+#             */
/*   Updated: 2020/10/10 20:33:04 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_NM_H__
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

typedef struct		s_nm
{
	uint64_t		n_value;
	int				n_sect;
	char			*n_strx;
	int				n_type;
	int				n_ext;
}					t_nm;

typedef struct		nlist_64 t_nlist_64;
typedef struct		nlist t_nlist;
typedef struct		section t_section;
typedef struct		section_64 t_section_64;
typedef struct		load_command t_load_command;
typedef struct		load_command_64 t_load_command_64;
typedef struct		segment_command t_segment_command;
typedef struct		segment_command_64 t_segment_command_64;
typedef struct		mach_header t_mach_header;
typedef struct		mach_header_64 t_mach_header_64;
typedef struct		symtab_command t_symtab_command;
typedef struct		symtab_command_64 t_symtab_command_64;
#endif
