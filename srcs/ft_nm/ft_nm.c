/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 04:29:16 by araout            #+#    #+#             */
/*   Updated: 2021/01/11 18:33:32 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int				main(int ac, char **av)
{
	int		i;
	int		res;
	int		flag;

	i = 0;
	if (ac == 1)
	{
		if ((res = handle_file("./a.out", 0)) != 0)
		{
			print_error(res, "./a.out");
			return (1);
		}
	}
	else
	{
		while (ac-- > 1)
		{
			if (ac > 1)
				flag = 1;
			if ((res = handle_file(av[++i], flag)) != 0)
				print_error(res, av[i]);
		}
	}
	return (0);
}

void			reset_section(void)
{
	g_sections.index = 0;
	g_sections.bss = 0;
	g_sections.data = 0;
	g_sections.text = 0;
	g_sections.swap = 0;
	g_sections.is_set = 0;
}

int				nm(char *ptr, off_t size, char *filename)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	reset_section();
	if (magic_number == AR_MAGIC || magic_number == AR_CIGAM)
		return (handle_archive(ptr, size, filename));
	else if(magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		return (handle_32(ptr, size));
	else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		return (handle_64(ptr, size));
	else if (magic_number == FAT_CIGAM_64 || magic_number == FAT_MAGIC_64)
		return (handle_fat_64(ptr, size, filename));
	else if (magic_number == FAT_CIGAM || magic_number == FAT_MAGIC)
		return (handle_fat_32(ptr, size, filename));
	return (ERR_FILE_FORMAT);
}

int				handle_file(char *filename,int flag)
{
	int				fd;
	char			*ptr;
	struct stat		buf;
	int				nm_ret;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ERR_OPEN);
	if (fstat(fd, &buf) < 0)
		return (ERR_FSTAT);
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (ERR_MMAP);
	ptr[buf.st_size -1] = '\0';
	if (flag == 1)
		ft_printf("\n%s:\n", filename);
	nm_ret = nm(ptr, buf.st_size, filename);
	if (munmap(ptr, buf.st_size) < 0)
		return (ERR_MUNMAP);
	close(fd);
	return (nm_ret);
}

void			print_error(int err, char *f)
{
	if (err == ERR_FILE_CORRUPT)
		ft_printf_fd(2, "ft_nm: error: %s : file is corrputed.\n", f);
	else if (err == ERR_FILE_FORMAT)
		ft_printf_fd(2, "ft_nm: error: %s : file format unrecognized\n", f);
	if (errno == EPERM)
		ft_printf_fd(2, "ft_nm: error: %s : Operation not permitted.\n", f);
	else if (errno == ENOENT)
		ft_printf_fd(2, "ft_nm: error: %s : No such file or directory.\n", f);
	else if (errno == EACCES)
		ft_printf_fd(2, "ft_nm: errror: %s : Permission denied.\n", f);
	else if (errno == EISDIR)
		ft_printf_fd(2, "ft_nm: error: %s : Is a directory.\n", f);
	else if (errno == ENFILE || errno == EMFILE)
		ft_printf_fd(2, "ft_nm: error: %s : too many open files.\n", f);
	else if (errno == EFBIG)
		ft_printf_fd(2, "ft_nm: error: %s : File too large.\n", f);
	else if (errno == EROFS)
		ft_printf_fd(2, "ft_nm: error: %s : Read-only file system.\n", f);
	else if (errno == EINTR)
		ft_printf_fd(2, "ft_nm: error:  Interrupted system call\n");
	else if (errno == ENOSPC)
		ft_printf_fd(2, "ft_nm: error: No space left on device.\n");
	else if (errno == ENOMEM)
		ft_printf_fd(2, "ft_nm: error: Cannot allocate memory.\n");
	else if (errno == ENAMETOOLONG)
		ft_printf_fd(2, "ft_nm: error: %s file name too long",f);
}
