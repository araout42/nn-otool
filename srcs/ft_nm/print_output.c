/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:41:18 by araout            #+#    #+#             */
/*   Updated: 2020/10/19 20:18:00 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

static int		print_ext(t_nm *nm)
{
	if (nm->n_type == N_ABS)
		ft_printf("a ");
	else if (nm->n_type == N_INDR)
		ft_printf("i ");
	else if (nm->n_type == N_SECT)
	{
		if (nm->n_sect == g_sections.bss)
			ft_printf("b ");
		else if (nm->n_sect == g_sections.data)
			ft_printf("d ");
		else if (nm->n_sect == g_sections.text)
			ft_printf("t ");
		else
			ft_printf("s ");
	}
	else
		return (-1);
	return (0);
}

static void		print_output2(t_nm *nm, int flag)
{
	(void)flag;
	if (nm->n_type == N_ABS)
		ft_printf("A ");
	else if (nm->n_type == N_INDR)
		ft_printf("I ");
	else if (nm->n_type == N_SECT && nm->n_ext)
	{
		if (nm->n_sect == g_sections.bss)
			ft_printf("B ");
		else if (nm->n_sect == g_sections.data)
			ft_printf("D ");
		else if (nm->n_sect == g_sections.text)
			ft_printf("T ");
		else
			ft_printf("S ");
	}
	else if (nm->n_type == N_UNDF && nm->n_sect == g_sections.bss)
			ft_printf("C ");
	else if (print_ext(nm) == -1)
		return ;
	ft_printf("%s\n", nm->n_strx);
}

void			print_output(t_nm *nm, int flag)
{
	if (ft_strlen(nm->n_strx) == 0)
		return ;
	if (nm->n_type == N_UNDF && nm->n_ext && nm->n_sect != g_sections.bss)
	{
		if (flag != 32)
			ft_printf("                 U %s\n", nm->n_strx);
		else
			ft_printf("         U %s\n", nm->n_strx);
	}
	else if (nm->n_type == N_ABS || nm->n_type == N_SECT
			|| nm->n_type == N_INDR || (nm->n_type == N_UNDF && nm->n_sect == g_sections.bss))
	{
		if (flag != 32)
			ft_printf("%0.16llx ", nm->n_value);
		else
			ft_printf("%0.8lx ", nm->n_value);
	}
	print_output2(nm, flag);
}
