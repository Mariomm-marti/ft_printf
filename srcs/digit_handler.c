/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 00:28:06 by mmartin-          #+#    #+#             */
/*   Updated: 2020/07/28 02:33:19 by mmartin-         ###   ########.fr       */
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

int			int_handle(char *out, t_flag *flag, int n)
{
	int		sent;
	int		zero;
	char	sign;

	sent = 0;
	sign = sign_picker(flag, &n);
	zero = flag->prec > ft_logn(10, n) ? flag->prec - ft_logn(10, n) - 1 : 0;
	printf("ZERO: %d\n\n", flag->prec);
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
