/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_ar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout </var/mail/araout>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:30:30 by araout            #+#    #+#             */
/*   Updated: 2020/10/28 08:14:46 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>
/*
   int		handle_archive(char *ptr, size_t size)
   {
   t_ar_hdr	*header;
   char		*str;
   size_t		len;

   ptr += SARMAG;
   header = (t_ar_hdr *)ptr;
   ptr += ft_atoi(header->ar_size) + sizeof(t_ar_hdr);
   while (ptr)
   {
   header = (t_ar_hdr *)ptr;
   if (ft_atoi(header->ar_size) <= 0)
   return (EXIT_FAILURE);
   str = ptr + sizeof(t_ar_hdr);
   if (ptr + (ft_atoi(header->ar_size) + sizeof(t_ar_hdr)) > ptr + size)
   return (EXIT_FAILURE);
   len = ft_strlen(str);
   while (!str[len++])
   ;
   nm(ptr + sizeof(t_ar_hdr) + len - 1, size);
   ptr += ft_atoi(header->ar_size) + sizeof(t_ar_hdr);
   }
   return (0);
   }
   */

int			handle_archive(void *ptr, off_t s, char *filename)
{
	struct ar_hdr	*header;
	char			*str;
	size_t			len;

	ptr += SARMAG;
	header = (						struct ar_hdr *)ptr;
	ptr += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	while (ptr)
	{
		header = (struct ar_hdr *)ptr;
		if (ft_atoi(header->ar_size) <= 0)
			return (EXIT_FAILURE);
		str = ptr + sizeof(struct ar_hdr);
		if (ptr + (ft_atoi(header->ar_size) + sizeof(struct ar_hdr)) > ptr + s)
			return (EXIT_FAILURE);
		if (ft_strcmp(str, "Makefile"))
		ft_printf("\n%s(%s):\n", filename, str);
		len = ft_strlen(str);
		while (!str[len++])
			;
		nm(ptr + sizeof(struct ar_hdr) + len - 1, s, NULL);
		ptr += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	}
	return (EXIT_SUCCESS);
}
