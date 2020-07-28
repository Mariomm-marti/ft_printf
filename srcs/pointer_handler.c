/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 00:02:47 by mmartin-          #+#    #+#             */
/*   Updated: 2020/07/28 02:03:37 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "libft/includes/libft.h"

/*
**	Converts ptr literal integer _num_ to it HEX value
*/

static int	convert_addr(char *out, unsigned long int num)
{
	unsigned int const	hexln = ft_logn(16, num);

	if (num == 0 && (*out = '0'))
		return (1);
	while (num > 0)
	{
		*(out-- + hexln) = "0123456789abcdef"[num % 16];
		num /= 16;
	}
	return (hexln + 1);
}

int			ptr_handle(char *out, t_flag *flag, void const *ptr)
{
	int				sent;
	int				sentptr;
	int				ptrlen;
	unsigned char	nullptr;

	sent = 0;
	if (flag->zero && flag->prec < 0)
		flag->prec = flag->width - 2;
	ptrlen = ft_logn(16, (unsigned long int)ptr) + 1;
	nullptr = !flag->prec && !(unsigned long int)ptr;
	nullptr = flag->prec && !(unsigned long int)ptr ? 2 : nullptr;
	flag->prec = flag->prec > ptrlen ? flag->prec - ptrlen : 0;
	while (!flag->left && sent < flag->width -
				(nullptr ? 1 + nullptr : ptrlen + 2) - flag->prec)
		*(out + sent++) = ' ';
	*(out + sent++) = '0';
	*(out + sent++) = 'x';
	sentptr = -1;
	while (++sentptr < flag->prec)
		*(out + sent++) = '0';
	if (nullptr != 1)
		sent += convert_addr(out + sent, (unsigned long int)ptr);
	while (flag->left && sent < flag->width)
		*(out + sent++) = ' ';
	return (sent);
}
