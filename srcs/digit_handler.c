/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 00:28:06 by mmartin-          #+#    #+#             */
/*   Updated: 2020/08/09 14:58:17 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <libft.h>

/*
**	Helps program decide the sign for the digit
*/

static char	sign_picker(t_flag const *flag, long long int *num)
{
	char	sign;

	sign = 0;
	if (*num < 0)
	{
		*num = -*num;
		sign = '-';
	}
	else if (flag->plus)
		sign = '+';
	else if (flag->space)
		sign = ' ';
	return (sign);
}

/*
**	DESCRIPTION
**		Given the arguments that should be considered for specifier d,
**		write into _out_ the result
**	RETURN VALUES
**		Returns the number of characters sent to _out_
*/

int			int_handle(char *out, t_flag *flag, long long int n)
{
	int		sent;
	int		zero;
	char	sign;

	sent = 0;
	sign = sign_picker(flag, &n);
	zero = flag->prec > ft_logn(10, n) ? flag->prec - ft_logn(10, n) - 1 : 0;
	if (flag->zero && flag->prec < 0)
		zero = flag->width - ft_logn(10, n) - !!sign - 1;
	while (!flag->left && sent < flag->width - !!sign - zero -
			ft_logn(10, n) - !(!flag->prec && !n))
		*(out + sent++) = ' ';
	if (sign)
		*(out + sent++) = sign;
	while (zero-- > 0)
		*(out + sent++) = '0';
	sent += !n && !flag->prec ? 0 : ft_itoa_base(out + sent, n, "0123456789");
	while (flag->left && sent < flag->width)
		*(out + sent++) = ' ';
	return (sent);
}

/*
**	DESCRIPTION
**		Given the arguments that should be considered for specifier u,
**		write into _out_ the result
**	RETURN VALUES
**		Returns the number of characters sent to _out_
*/

int			uint_handle(char *out, t_flag *flag, unsigned long long int n)
{
	int		sent;
	int		zero;

	sent = 0;
	zero = flag->prec > ft_logn(10, n) ? flag->prec - ft_logn(10, n) - 1 : 0;
	if (flag->zero && flag->prec < 0)
		zero = flag->width - ft_logn(10, n) - 1;
	while (!flag->left && sent < flag->width - zero -
			ft_logn(10, n) - !(!flag->prec && !n))
		*(out + sent++) = ' ';
	while (zero-- > 0)
		*(out + sent++) = '0';
	sent += !n && !flag->prec ? 0 : ft_itoa_base(out + sent, n, "0123456789");
	while (flag->left && sent < flag->width)
		*(out + sent++) = ' ';
	return (sent);
}

/*
**	DESCRIPTION
**		Given the arguments that should be considered for specifier x and X,
**		write into _out_ the result
**	RETURN VALUES
**		Returns the number of characters sent to _out_
*/

int			hex_handle(char *out, t_flag *flag,
							unsigned long long int n, char const *base)
{
	int		sent;
	int		zero;

	sent = 0;
	zero = flag->prec > ft_logn(16, n) ? flag->prec - ft_logn(16, n) - 1 : 0;
	flag->sharp = !n ? 0 : flag->sharp;
	if (flag->zero && flag->prec < 0)
		zero = flag->width - ft_logn(16, n) - 1 - (flag->sharp ? 2 : 0);
	while (!flag->left && sent < flag->width - zero -
			ft_logn(16, n) - !(!flag->prec && !n) - (flag->sharp ? 2 : 0))
		*(out + sent++) = ' ';
	if (flag->sharp && (*(out + sent++) = '0'))
		*(out + sent++) = *(base + 15) == 'F' ? 'X' : 'x';
	while (zero-- > 0)
		*(out + sent++) = '0';
	sent += !n && !flag->prec ? 0 :
				ft_itoa_base(out + sent, n, base);
	while (flag->left && sent < flag->width)
		*(out + sent++) = ' ';
	return (sent);
}
