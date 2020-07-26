/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 02:24:47 by mmartin-          #+#    #+#             */
/*   Updated: 2020/07/26 18:02:52 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef FT_PRINTF_MAXL
#  define FT_PRINTF_MAXL 8192
# endif

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

# pragma pack(1)

typedef struct		s_flag
{
	int				width;
	int				prec;
	unsigned char	left : 1;
	unsigned char	zero : 1;
	unsigned char	sharp : 1;
	unsigned char	space : 1;
	unsigned char	plus : 1;
}					t_flag;

# pragma options align=reset

int					ft_sprintf(char *out, char const *format, ...);
int					ft_printfd(int const fd, char const *format, ...);
int					ft_printf(char const *format, ...);

#endif
