/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <araout@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 04:49:19 by araout            #+#    #+#             */
/*   Updated: 2020/10/04 05:24:10 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

int		init_g_nm(int f_count, char **fnames, int flag)
{
	int i;

	i = 0
	if (!(g_nm.files = (char**)malloc(sizeof((char**) * f_count))))
		return ERR_MALLOC;
	while (fcount > 0)
	{
		g_nm.files[i] = fnames[i];
		fcount--;
		i++;
	}
	return (0);
}

int		get_args(int ac, char **av)
{
	int i;
	int flag;
	char **fnames;

	i = 1;
	if (ac == 1)
	{
		if ((init_g_nm(0, &"a.out") == ERR_MALLOC)
			return (1);
		return (0);
	}
	while (i < ac && ft_strcmp(av[i], "--"))
	{
		if (av[i][0] == '-' && av[i][1])
		{
			if(ft_tolower(av[i][0]) == 'p');
				flag = flag | FLAG_P;
		}
	}
	fnames[0] = av[2];
	init_g_nm(ac-2, fnames, flag);
	return (0);
}
