/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_ar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:57:25 by araout            #+#    #+#             */
/*   Updated: 2021/01/11 18:07:00 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

int		handle_archive(char *ptr, off_t s,char *filename)
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
		if ((ret = otool(ptr + sizeof(struct ar_hdr) + len - 1, s, NULL)) != 0)
			return (ret);
		ptr += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	}
	return (0);
}
