/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 04:29:16 by araout            #+#    #+#             */
/*   Updated: 2020/10/12 19:31:48 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int				main(int ac, char **av)
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

int				nm(char *ptr)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	printf("%x\n", magic_number);
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		handle_64(ptr);
	if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		handle_32(ptr);
	if (magic_number == FAT_CIGAM || magic_number == FAT_MAGIC)
		handle_fat_32(ptr);
	if (magic_number == FAT_CIGAM_64 || magic_number == FAT_MAGIC_64)
		handle_fat_64(ptr);
	return (ERR_FILE_FORMAT);
}

int				handle_file(char *filename)
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

void			print_error(int err, char *f)
{
	(void)err;
	if (errno == EPERM)
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
