/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 04:29:16 by araout            #+#    #+#             */
/*   Updated: 2020/10/08 17:16:28 by araout           ###   ########.fr       */
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

int				symtab_64(t_symtab_command *sym, char *ptr)
{
	unsigned int				i;
	char			*strtable;
	t_nlist_64		*el;

	el = (void *)ptr + sym->symoff;
	strtable = (void *)ptr + sym->stroff;
	i = 0;
	while (sym->nsyms > i)
	{
		if (!el[i].n_value)
		{

			ft_printf("\t\t  %d %s\n", el[i].n_sect, strtable + el[i].n_un.n_strx);
		}
		else
		{
			ft_printf("%llx %d %s\n", el[i].n_value, el[i].n_sect, strtable + el[i].n_un.n_strx);
		}
		i++;
	}
	return (0);
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
		if (lc && lc->cmd == LC_SYMTAB)
		{
			symtab_64((t_symtab_command *)lc, ptr);
			break;
		}

		lc = (void *)lc + lc->cmdsize;
	}

	return (0);
}

int			nm(char *ptr)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(ptr);
	}
	if (magic_number == MH_MAGIC)
	{
		handle_32(ptr);
	}
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
