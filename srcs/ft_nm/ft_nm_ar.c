/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_ar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout </var/mail/araout>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:30:30 by araout            #+#    #+#             */
/*   Updated: 2021/01/11 17:08:27 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int			handle_archive(void *ptr, off_t s, char *filename)
{
	struct ar_hdr	*header;
	char			*str;
	size_t			len;
	int				ret;

	ptr += SARMAG;
	header = (struct ar_hdr *)ptr;
	ptr += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	while (ptr)
	{
		header = (struct ar_hdr *)ptr;
		if (ft_atoi(header->ar_size) <= 0)
			return (ERR_FILE_CORRUPT);
		str = ptr + sizeof(struct ar_hdr);
		if (ptr + (ft_atoi(header->ar_size) + sizeof(struct ar_hdr)) > ptr + s)
			return (ERR_FILE_CORRUPT);
		ft_printf("\n%s(%s):\n", filename, str);
		len = ft_strlen(str);
		while (!str[len++])
			;
		if ((ret = nm(ptr + sizeof(struct ar_hdr) + len - 1, s, NULL)) != 0)
			return (ret);
		ptr += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	}
	return (EXIT_SUCCESS);
}
