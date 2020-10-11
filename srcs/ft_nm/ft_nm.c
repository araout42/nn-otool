/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 04:29:16 by araout            #+#    #+#             */
/*   Updated: 2020/10/11 17:15:15 by araout           ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int			handle_32(char *ptr)
{
	t_mach_header			*header;
	int						ncmds;
	t_load_command			*lc;
	int						i;

	i = 0;
	header = (t_mach_header *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(t_mach_header);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			write(1, "SYMTAB", 6);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
	}

	return (0);
}

t_nm			*make_node(uint64_t n_value, int n_sect, char *n_strx, int type)
{
	t_nm		*nm;

	if (!(nm = ft_memalloc(sizeof(t_nm))))
		return (NULL);
	nm->n_value = n_value;
	nm->n_sect = n_sect;
	nm->n_strx = n_strx;
	nm->n_type = type & N_TYPE;
	nm->n_ext = type & N_EXT;
	return (nm);
}

int			print_ext(t_nm *nm)
{
	if (nm->n_type == N_ABS)
		ft_printf("a ");
	else if (nm->n_type == N_INDR)
		ft_printf("i ");
	else if (nm->n_type == N_SECT)
	{
		if (nm->n_sect  == sections.bss)
			ft_printf("b ");
		else if (nm->n_sect == sections.data)
			ft_printf("d ");
		else if (nm->n_sect == sections.text)
			ft_printf("t ");
		else
			ft_printf("s ");
	}
	else
		return (-1);
	return (0);
}

void			print_output(t_nm *nm)
{
	if (ft_strlen(nm->n_strx) == 0)
		return ;
	if (nm->n_type == N_UNDF && nm->n_ext)
		ft_printf("                 U %s\n", nm->n_strx);
	else if (nm->n_type == N_ABS || nm->n_type == N_SECT || nm->n_type == N_INDR)
		ft_printf("%0.16llx ", nm->n_value);
	if (nm->n_type == N_ABS)
		ft_printf("A ");
	else if (nm->n_type == N_INDR)
		ft_printf("I ");
	else if (nm->n_type == N_SECT && nm->n_ext)
	{
		if (nm->n_sect == sections.bss)
			ft_printf("B ");
		else if (nm->n_sect == sections.data)
			ft_printf("D ");
		else if (nm->n_sect == sections.text)
			ft_printf("T ");
		else
			ft_printf("S ");
	}
	else if (print_ext(nm) == -1)
		return ;
	//ft_printf("%s ------- %d\n", nm->n_strx, nm->n_sect);
	ft_printf("%s\n", nm->n_strx);
}

int			compare_ascii(t_list *a, t_list *b)
{
	return (ft_strcmp(((t_nm *)a->content)->n_strx,
				((t_nm *)b->content)->n_strx));
}

int			ft_sort_root(t_list **head, int flag)
{
	if (flag == 0)
		*head = mergesorti(*head, compare_ascii);
	return (1);
}

int				symtab_64(t_symtab_command *sym, char *ptr)
{
	unsigned int	i;
	char			*strtable;
	t_nlist_64		*el;
	t_list			*lst_begin;
	t_list			*lst;
	t_nm			*nm;

	el = (void *)ptr + sym->symoff;
	strtable = (void *)ptr + sym->stroff;
	lst_begin = NULL;
	lst = NULL;
	i = 0;
	while (sym->nsyms > i)
	{
		nm = make_node(el[i].n_value, el[i].n_sect, strtable + el[i].n_un.n_strx, el[i].n_type);
		if (!lst)
		{
			if (!(lst = ft_list_create((char *)nm, sizeof(nm))))
				return (-1);
			lst_begin = lst;
		}
		else
			if (!(ft_list_append(&lst_begin, (char *)nm, sizeof(nm))))
				return (-1);
		i++;
	}
	ft_sort_root(&lst_begin, 0);
	lst = lst_begin;
	while(lst)
	{
		nm = (t_nm *)lst->content;
		print_output(nm);
		lst = lst->next;
	}
	return (0);
}

static void		segment_64(t_load_command *lc)
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
			sections.text = sections.index + 1;
		else if (!ft_strcmp(sect->sectname, SECT_DATA)
				&& !ft_strcmp(sect->segname, SEG_DATA))
			sections.data = sections.index + 1;
		else if (!ft_strcmp(sect->sectname, SECT_BSS)
				&& !ft_strcmp(sect->segname, SEG_DATA))
			sections.bss = sections.index + 1;
		sect = sect + 1;
		sections.index++;
	}
}

int			handle_64(char *ptr)
{
	t_mach_header_64		*header;
	int						ncmds;
	t_load_command			*lc;
	int						i;


	i = -1;
	header = (t_mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(t_mach_header_64);
	while (++i < ncmds)
	{
		if (lc && lc->cmd == LC_SEGMENT_64)
			segment_64((t_load_command *)lc);
		if (lc && lc->cmd == LC_SYMTAB)
			symtab_64((t_symtab_command *)lc, ptr);
		lc = (void *)lc + lc->cmdsize;
	}

	return (0);
}

int			nm(char *ptr)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
	if (magic_number == MH_MAGIC)
		handle_32(ptr);
	return (ERR_FILE_FORMAT);
}
int			handle_file(char *filename)
{
	int				fd;
	char			*ptr;
	struct stat		buf;
	int				nm_ret;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ERR_OPEN);
	if (fstat(fd, &buf) < 0)
		return (ERR_FSTAT);
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (ERR_MMAP);
	nm_ret = nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (ERR_MUNMAP);
	close(fd);
	if (nm_ret == ERR_FILE_FORMAT)
		return (ERR_FILE_FORMAT);
	return (0);
}

void		print_error(int err, char *f)
{
	(void)err;
	if (errno ==  EPERM)
		ft_printf("ft_nm: error: %s : Operation not permitted.\n", f);
	else if (errno == ENOENT)
		ft_printf("ft_nm: error: %s : No such file or directory.\n", f);
	else if (errno == EACCES)
		ft_printf("ft_nm: errror: %s : Permission denied.\n", f);
	else if (errno == EISDIR)
		ft_printf("ft_nm: error: %s : Is a directory.\n", f);
	else if (errno == ENFILE || errno == EMFILE)
		ft_printf("ft_nm: error: %s : too many open files.\n", f);
	else if (errno == EFBIG)
		ft_printf("ft_nm: error: %s : File too large.\n", f);
	else if (errno == EROFS)
		ft_printf("ft_nm: error: %s : Read-only file system.\n", f);
	else if (errno == EINTR)
		ft_printf("ft_nm: error:  Interrupted system call\n");
	else if (errno == ENOSPC)
		ft_printf("ft_nm: error: No space left on device.\n");
	else if (errno == ENOMEM)
		ft_printf("ft_nm: error: Cannot allocate memory.\n");
	else if (errno == ENAMETOOLONG)
		ft_printf("ft_nm: error: %s file name too long", f);
}


int			main(int ac, char **av)
{
	int		i;
	int		res;

	i = 0;
	if (ac == 1)
	{
		if ((res = handle_file("./a.out")) != 0)
		{
			print_error(res, "./a.out");
			return (1);
		}
	}
	else
	{
		while (ac-- > 1)
		{
			if ((res = handle_file(av[++i])) != 0)
			print_error(res, av[i]);
		}
	}
	return (0);
}
