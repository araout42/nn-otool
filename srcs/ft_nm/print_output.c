/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:41:18 by araout            #+#    #+#             */
/*   Updated: 2021/01/04 11:59:21 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void			print_output(t_nm *nm, int flag)
{
	if (ft_strlen(nm->n_strx) == 0)
		return ;
	if (nm->n_type == N_UNDF && nm->n_ext && !nm->n_value)
	{
		if (flag != 32)
			ft_printf("                 %c %s\n", nm->key, nm->n_strx);
		else
			ft_printf("         %c %s\n", nm->key, nm->n_strx);
	}
	else if (nm->n_type == N_ABS || nm->n_type == N_SECT
			|| nm->n_type == N_INDR || (nm->n_ext && nm->n_value))
	{
		if (flag != 32)
			ft_printf("%0.16llx ", nm->n_value);
		else
			ft_printf("%0.8lx ", nm->n_value);
		ft_printf("%c %s\n", nm->key, nm->n_strx);
	}
//	else
//		ft_printf("%c %s\n", nm->key, nm->n_strx);
}
