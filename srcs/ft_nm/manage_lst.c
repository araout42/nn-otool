/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:44:32 by araout            #+#    #+#             */
/*   Updated: 2020/10/12 17:58:39 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

t_nm			*make_node(uint64_t n_value, int n_sect, char *n_strx, int type)
{
	t_nm		*nm;

	if (!(nm = ft_memalloc(sizeof(t_nm))))
		return (NULL);
	nm->n_value = n_value;
	nm->n_sect = n_sect;
	nm->n_strx = n_strx;
	nm->n_type = type & N_TYPE;
	nm->n_ext = type & N_EXT;
	return (nm);
}

int				compare_ascii(t_list *a, t_list *b)
{
	return (ft_strcmp(((t_nm *)a->content)->n_strx,
				((t_nm *)b->content)->n_strx));
}

int				ft_sort_root(t_list **head, int flag)
{
	if (flag == 0)
		*head = mergesorti(*head, compare_ascii);
	return (1);
}

t_list			*build_lst(t_symtab_command *sym, char *strtbl, t_nlist_64 *el)
{
	t_list			*lst;
	t_list			*lst_begin;
	t_nm			*nm;
	unsigned int	i;

	i = 0;
	while (sym->nsyms > i)
	{
		nm = make_node(el[i].n_value, el[i].n_sect,
				strtbl + el[i].n_un.n_strx, el[i].n_type);
		if (!lst)
		{
			if (!(lst = ft_list_create((char *)nm, sizeof(nm))))
				return (NULL);
			lst_begin = lst;
		}
		else if (!(ft_list_append(&lst_begin, (char *)nm, sizeof(nm))))
			return (NULL);
		i++;
	}
	return (lst_begin);
}
