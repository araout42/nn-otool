/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:44:32 by araout            #+#    #+#             */
/*   Updated: 2021/01/11 18:32:09 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm.h>

void			get_letter_key(t_nm *nm)
{
	if (ft_strlen(nm->n_strx) == 0)
		return ;
	if (nm->n_type == N_UNDF && nm->n_ext)
	{
		nm->key = 'U';
	}
	if (nm->n_type == N_ABS)
		nm->key = 'A';
	else if (nm->n_type == N_INDR)
		nm->key = 'I';
	else if (nm->n_type == N_SECT && nm->n_ext)
	{
		if (nm->n_sect == g_sections.bss)
			nm->key = 'B';
		else if (nm->n_sect == g_sections.data)
			nm->key = 'D';
		else if (nm->n_sect == g_sections.text)
			nm->key = 'T';
		else
			nm->key = 'S';
	}
	else if (nm->n_ext && nm->n_value)
			nm->key = 'C';
	else if (nm->n_type == N_ABS)
		nm->key = 'a';
	else if (nm->n_type == N_INDR)
		nm->key = 'i';
	else if (nm->n_type == N_SECT)
	{
		if (nm->n_sect == g_sections.bss)
			nm->key = 'b';
		else if (nm->n_sect == g_sections.data)
			nm->key = 'd';
		else if (nm->n_sect == g_sections.text)
			nm->key = 't';
		else
			nm->key = 's';
	}
}


void ft_cleanode(void *content)
{
	t_nm	*nm;

	nm = content;
	free(nm->n_strx);
	free(nm);
}

void		free_lst(t_list **lst)
{
	t_list	*tmp;
	t_list	*head;

	tmp = NULL;
	head = *lst;
	while (head)
	{
		tmp = head;
		head = head->next;
		ft_cleanode(tmp->content);
		free(tmp);
		tmp = NULL;
	}
}

t_nm			*make_node(uint64_t n_value, int n_sect, char *n_strx, int type)
{
	t_nm		*nm;
	if (!(nm = ft_memalloc(sizeof(t_nm))))
		return (NULL);
	nm->n_value = SWAPIF64(n_value);
	nm->n_sect = n_sect;
	nm->n_strx = ft_strdup(n_strx);
	nm->n_type = type & N_TYPE;
	nm->n_ext = type & N_EXT;
	get_letter_key(nm);
	return (nm);
}

t_nm			*make_node32(uint32_t n_value, int n_sect, char *n_strx, int type)
{
	t_nm		*nm;
	if (!(nm = ft_memalloc(sizeof(t_nm))))
		return (NULL);
	nm->n_value = SWAPIF(n_value);
	nm->n_sect = n_sect;
	nm->n_strx = ft_strdup(n_strx);
	nm->n_type = type & N_TYPE;
	nm->n_ext = type & N_EXT;
	get_letter_key(nm);
	return (nm);
}

int				compare_ascii(t_list *a, t_list *b)
{
	if (ft_strcmp(((t_nm *)a->content)->n_strx,
				((t_nm *)b->content)->n_strx) == 0)
	if (ft_strcmp(&((t_nm *)a->content)->key,
				&((t_nm *)b->content)->key) == 0)
		{
			if (((t_nm*)a->content)->n_value > ((t_nm *)b->content)->n_value)
				return (1);
			else if (((t_nm*)a->content)->n_value == ((t_nm *)b->content)->n_value)
				return (1);
			else
				return (-1);
		}
	else
		return (ft_strcmp(&((t_nm *)a->content)->key, &((t_nm *)b->content)->key));
	else
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
	lst = NULL;
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
