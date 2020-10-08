/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:39:42 by araout            #+#    #+#             */
/*   Updated: 2020/10/05 13:50:14 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/errno.h>

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
