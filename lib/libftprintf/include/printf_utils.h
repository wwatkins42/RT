/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 15:05:49 by scollon           #+#    #+#             */
/*   Updated: 2016/03/13 11:56:51 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_UTILS_H
# define PRINTF_UTILS_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>
# include <stdint.h>
# include <limits.h>

typedef struct	s_flg
{
	int		pl;
	int		mn;
	int		sp;
	int		di;
	int		zr;
}				t_flg;

typedef struct	s_prc
{
	int		pt;
	int		prec;
}				t_prc;

typedef struct	s_mod
{
	int		h;
	int		hh;
	int		l;
	int		ll;
	int		j;
	int		z;
}				t_mod;

typedef struct	s_a
{
	t_flg		flag;
	long int	width;
	t_prc		prec;
	t_mod		mod;
	char		type;
	int			null;
	int			out;
}				t_a;

typedef struct	s_e
{
	int			alen;
	int			plen;
	int			out;
	va_list		ap;
}				t_e;

/*
**				functions used to parse format
*/
int				parse_format(const char *format, t_a *arg, t_e *e);
int				get_flags(const char *format, int i, t_a *arg);
int				get_mod(const char *format, int i, t_a *arg);
int				get_prec(const char *format, int i, t_a *arg);
int				get_type(const char *format, int i, t_a *arg);
int				get_width(const char *format, int i, t_a *arg);
int				is_mod(char md);
int				is_flag(char fl);
int				is_type(char ty);
int				check_err(t_a *arg);

/*
**				functions used to print arg
*/
int				print_arg(t_e *e, t_a *arg);
void			print_arg_notype(t_e *e, t_a *arg, int *i);
void			print_arg_int(t_e *e, t_a *arg, int *i);
void			print_arg_unsigned(t_e *e, t_a *arg, int *i);
void			print_arg_char(t_e *e, t_a *arg, int *i);
void			print_arg_str(t_e *e, t_a *arg, int *i);
void			print_arg_base(t_e *e, t_a *arg, int *i);
void			print_arg_ptr(t_e *e, t_a *arg, int *i);
void			print_arg_float(t_e *e, t_a *a, int *i);

/*
**		UTILS
*/
int				nbr_len(long long int n);
int				nbr_len_unsigned(unsigned long long int n);
int				nbr_len_base(long n, const int base);
int				nbr_binary(unsigned int v);
int				str_len(const char *s);
int				print_int(long long int n, t_a *arg);
int				print_unsigned_int(unsigned long long int n, t_a *arg);
int				print_char(t_a *arg, char c);
int				print_str(const char *s, t_a *arg);
int				print_wchar(t_a *arg, unsigned int c);
int				print_wstr(const wchar_t *s, t_a *arg);
int				print_base(t_a *arg, unsigned long long n, const int base,
							char maj);
int				print_mem(void *p, t_a *arg);

#endif
