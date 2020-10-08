/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 04:32:17 by araout            #+#    #+#             */
/*   Updated: 2020/10/08 17:00:09 by araout           ###   ########.fr       */
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
/*
 ** MACH-O FORMAT
*/


typedef unsigned char				uint8_t;
typedef unsigned short int			uint16_t;
# ifndef __uint32_t_defined
typedef unsigned int				uint32_t;
#  define __uint32_t_defined
# endif
typedef unsigned long long int		 uint64_t;

typedef int32_t					integer_t;
typedef integer_t				cpu_type_t;
typedef integer_t				cpu_subtype_t;
typedef integer_t				cpu_threadtype_t;



typedef struct		s_nm
{
	char			**files;
	int				file_count;
	int				flag;
}					t_nm;

t_nm				g_nm;

typedef struct		mach_header {
	uint32_t		magic;
	cpu_type_t		cputype;
	cpu_subtype_t	cpusubtype;
	uint32_t		filetype;
	uint32_t		ncmds;
	uint32_t		sizeofcmds;
	uint32_t		flags;
}					t_mach_header;

# define MH_MAGIC 0xfeedface
# define MH_CIGAM 0xcefaedfe

typedef struct		mach_header_64 {
	uint32_t		magic;
	cpu_type_t		cputype;
	cpu_subtype_t	cpusubtype;
	uint32_t		filetype;
	uint32_t		ncmds;
	uint32_t		sizeofcmds;
	uint32_t		flags;
	uint32_t		reserved;
}					t_mach_header_64;

#define MH_MAGIC_64 0xfeedfacf
#define MH_CIGAM_64 0xcffaedfe

typedef struct		load_command {
	uint32_t		cmd;           /* type of load command */
	uint32_t		cmdsize;       /* total size of command in bytes */
}					t_load_command;


# define LC_SYMTAB 0x2

typedef struct		symtab_command {
	uint32_t		cmd;            /* LC_SYMTAB */
	uint32_t		cmdsize;        /* sizeof(struct symtab_command) */
	uint32_t		symoff;         /* symbol table offset */
	uint32_t		nsyms;          /* number of symbol table entries */
	uint32_t		stroff;         /* string table offset */
	uint32_t		strsize;        /* string table size in bytes */
}					t_symtab_command;

typedef struct		nlist {
	union {
#ifndef __LP64__
		char *		n_name;   /* for use when in-core */
#endif
		uint32_t	n_strx;        /* index into the string table */
	}				n_un;
	uint8_t			n_type;         /* type flag, see below */
	uint8_t			n_sect;         /* section number or NO_SECT */
	int16_t			n_desc;         /* see <mach-o/stab.h> */
	uint32_t		n_value;       /* value of this symbol (or stab offset) */
}					t_nlist;

/*
 * This is the symbol table entry structure for 64-bit architectures.
 */
typedef struct		nlist_64 {
	union {
		uint32_t	n_strx; /* index into the string table */
	}				n_un;
	uint8_t			n_type;        /* type flag, see below */
	uint8_t			n_sect;        /* section number or NO_SECT */
	uint16_t		n_desc;       /* see <mach-o/stab.h> */
	uint64_t		n_value;      /* value of this symbol (or stab offset) */
}					t_nlist_64;


#endif
