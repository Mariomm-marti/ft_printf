/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 00:28:06 by mmartin-          #+#    #+#             */
/*   Updated: 2020/07/28 00:33:29 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "libft/includes/libft.h"

/*
**	Helps program decide the sign for the digit
*/

static char	sign_picker(t_flag const *flag, int *num)
{
	char	sign;

	sign = flag->space ? ' ' : 0;
	sign = flag->plus ? '+' : sign;
	if (*num < 0)
	{
		*num = -*num;
		sign = '-';
	}
	return (sign);
}

int			int_handle(char *out, t_flag *flag, int num)
{
	int				sent;
	int				sentptr;
	int				nl;
	char			sn;
	unsigned char	is_exc;

	sent = 0;
	nl = ft_countdigits(num);
	sn = sign_picker(flag, &num);
	is_exc = !num && !flag->prec;
	if (flag->zero && flag->prec < 0)
		flag->prec = flag->width - (sn > 0);
	flag->prec = flag->prec > nl ? flag->prec - nl + (sn == '-') : 0;
	while (!flag->left && sent < flag->width - flag->prec -
				nl - (flag->zero) + (sn > 0) + is_exc)
		*(out + sent++) = ' ';
	if (sn)
		*(out + sent++) = sn;
	sentptr = -1;
	while (++sentptr < flag->prec)
		*(out + sent++) = '0';
	sent += is_exc ? 0 : ft_itoa_base(out + sent, num, "0123456789");
	while (flag->left && sent < flag->width)
		*(out + sent++) = ' ';
	return (sent);
}
