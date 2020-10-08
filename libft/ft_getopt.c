/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <araout@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 05:53:47 by araout            #+#    #+#             */
/*   Updated: 2020/10/04 06:21:12 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*getopt(char **av, int ac, char *opts)
{
	char	ret[100];
	int		i;
	int		j;
	int		k;
	int		opts_count;

	opts_count = 0;
	k = 0;
	i = 0;
	j = 1;
	while (i < ac  && ft_strcmp(av[i], "--"))
	{
		if (av[i][0] && av[i][0] == '-' && av[i][1])
		{
			while(av[i][j] && av[i][j] != ' ')
			{
				if (ft_strchr(opts, av[i][j]))
				{
					
				}
				j++;
			}
			j = 1;
		}
	}
	return ("blabla");
}
