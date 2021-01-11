/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 04:29:16 by araout            #+#    #+#             */
/*   Updated: 2021/01/11 18:15:19 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

int				main(int ac, char **av)
{
	int		i;
	int		res;

	while (1)
	{
	i = 0;
	if (ac == 1)
	{
		ft_printf_fd(2, "error : ft_otool: at least one file must be specified\n");
		exit(1);
	}
	else
	{
		while (ac-- > 1)
		{
			if ((res = handle_file(av[++i])) != 0)
				print_error(res, av[i]);
		}
		ac = 2;
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

int				otool(char *ptr, off_t size, char *filename)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	reset_section();
	if (magic_number == AR_MAGIC || magic_number == AR_CIGAM)
	{
		if (filename)
			ft_printf("%s:\n",filename);
		return (handle_archive(ptr, size, filename));
	}
	else if(magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
		if (filename)
			ft_printf("%s:\n",filename);
		return (handle_32(ptr, size));
	}
	else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		if (filename)
			ft_printf("%s:\n",filename);
		return (handle_64(ptr, size));
	}
	else if (magic_number == FAT_CIGAM_64 || magic_number == FAT_MAGIC_64)
	{
		if (filename)
			ft_printf("%s:\n",filename);
		return (handle_fat_64(ptr, size, filename));
	
	}
	else if (magic_number == FAT_CIGAM || magic_number == FAT_MAGIC)
	{
		if (filename)
			ft_printf("%s:\n",filename);
		return (handle_fat_32(ptr, size, filename));
	}
	return (ERR_FILE_FORMAT);
}

int				handle_file(char *filename)
{
	int				fd;
	char			*ptr;
	struct stat		buf;
	int				otool_ret;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ERR_OPEN);
	if (fstat(fd, &buf) < 0)
		return (ERR_FSTAT);
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (ERR_MMAP);
	ptr[buf.st_size -1] = '\0';
	otool_ret = otool(ptr, buf.st_size, filename);
	if (munmap(ptr, buf.st_size) < 0)
		return (ERR_MUNMAP);
	close(fd);
	return (otool_ret);
}

void			print_error(int err, char *f)
{
	if (err == ERR_FILE_CORRUPT)
		ft_printf_fd(2, "ft_otool: error: %s : file is corrputed.\n", f);
	else if (err == ERR_FILE_FORMAT)
		ft_printf_fd(2, "ft_otool: error: %s : file format unrecognized\n", f);
	if (errno == EPERM)
		ft_printf_fd(2, "ft_otool: error: %s : Operation not permitted.\n", f);
	else if (errno == ENOENT)
		ft_printf_fd(2, "ft_otool: error: %s : No such file or directory.\n", f);
	else if (errno == EACCES)
		ft_printf_fd(2, "ft_otool: errror: %s : Permission denied.\n", f);
	else if (errno == EISDIR)
		ft_printf_fd(2, "ft_otool: error: %s : Is a directory.\n", f);
	else if (errno == ENFILE || errno == EMFILE)
		ft_printf_fd(2, "ft_otool: error: %s : too many open files.\n", f);
	else if (errno == EFBIG)
		ft_printf_fd(2, "ft_otool: error: %s : File too large.\n", f);
	else if (errno == EROFS)
		ft_printf_fd(2, "ft_otool: error: %s : Read-only file system.\n", f);
	else if (errno == EINTR)
		ft_printf_fd(2, "ft_otool: error:  Interrupted system call\n");
	else if (errno == ENOSPC)
		ft_printf_fd(2, "ft_otool: error: No space left on device.\n");
	else if (errno == ENOMEM)
		ft_printf_fd(2, "ft_otool: error: Cannot allocate memory.\n");
	else if (errno == ENAMETOOLONG)
		ft_printf_fd(2, "ft_otool: error: %s file name too long",f);
}
