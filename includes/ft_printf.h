/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 02:24:47 by mmartin-          #+#    #+#             */
/*   Updated: 2020/07/28 03:24:52 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef FT_PRINTF_MAXL
#  define FT_PRINTF_MAXL 16384
# endif

# ifndef FT_PRINTF_L
#  define FT_PRINTF_L "0123456789abcdef"
# endif

# ifndef FT_PRINTF_U
#  define FT_PRINTF_U "0123456789ABCDEF"
# endif

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

# pragma pack(1)

typedef struct	s_flag
{
	int				width;
	int				prec;
	unsigned char	left : 1;
	unsigned char	zero : 1;
	unsigned char	sharp : 1;
	unsigned char	space : 1;
	unsigned char	plus : 1;
}				t_flag;

# pragma options align=reset

int				char_handle(char *out, t_flag const *flag, char const chr);
int				string_handle(char *out, t_flag const *flag, char const *str);
int				ptr_handle(char *out, t_flag *flag, void const *ptr);
int				int_handle(char *out, t_flag *flag, long long int n);
int				uint_handle(char *out, t_flag *flag, unsigned long long int n);
int				hex_handle(char *out, t_flag *flag,
								unsigned long long int n, char const *base);

int				sprintf_wrapper(char *out, char const *form, va_list args);
int				ft_sprintf(char *out, char const *format, ...);
int				ft_printfd(int const fd, char const *format, ...);
int				ft_printf(char const *format, ...);

#endif
