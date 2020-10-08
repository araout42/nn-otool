/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 22:46:47 by kicausse          #+#    #+#             */
/*   Updated: 2020/10/05 14:20:10 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# define OPTIONS ("cCsSpdDioOuUxXfFbr")
# include "specifiers.h"

int					is_option(char c);
int					search_reverse(char *str, char c, int start);
int					flag(int nbr, int flags);
int					is_valid_size_flag(char c);
int					charset_match_c(char *s, char c);
int					is_printable(int print, t_spec *spec, int *maxlen);
unsigned long long	read_ullong(void *n);
int					ft_adv_memcmp(const void *source, const char *hexdata);
size_t				ft_putnstr_non_printable(char *str, size_t n);
#endif