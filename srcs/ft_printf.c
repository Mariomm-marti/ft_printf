/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 02:13:08 by mmartin-          #+#    #+#             */
/*   Updated: 2020/07/28 00:21:47 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "libft/includes/libft.h"

static char	sign_picker(t_flag const *flag, int *num)
{
	char	sign;

	sign = flag->space ? ' ' : 0;
	sign = flag->plus ? '+' : sign;
	return (num < 0 && (*num = -*num) ? '-' : sign);
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
	flag->prec = flag->zero && flag->prec < 0 ? flag->width : flag->prec;
	flag->prec = flag->prec > nl ? flag->prec - nl + (sn == '-') : 0;
	while (!flag->left && sent < flag->width - flag->prec -
				nl - flag->zero + is_exc)
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

/*
**	DESCRIPTION
**		Gives full control over behaviour of printing. Output is sent to
**		_out_, using _form_ as text formatting
**	RETURN VALUES
**		Number of copied characters to _out_. Although _out_ may have content,
**		if something went wrong -1 will be the returned value
*/

int			ft_sprintf(char *out, char const *form, ...)
{
	va_list	args;
	int		printedc;

	va_start(args, form);
	printedc = sprintf_wrapper(out, form, args);
	va_end(args);
	return (printedc);
}

/*
**	DESCRIPTION
**		Allows printing to the specified filedescriptor _fd_, text formatted
**		using _form_
**	RETURN VALUES
**		Number of printed characters to _fd_, -1 if something went wrong
*/

int			ft_printfd(int const fd, char const *form, ...)
{
	char	out[FT_PRINTF_MAXL];
	va_list	args;
	int		printedc;

	va_start(args, form);
	printedc = sprintf_wrapper(out, form, args);
	va_end(args);
	if (printedc >= 0)
		write(fd, out, printedc);
	return (printedc);
}

/*
**	DESCRIPTION
**		Allows to print using the format first parameter. Result will be
**		printed to STDOUT
**	RETURN VALUES
**		Number of printed characters, -1 if something went wrong
*/

int			ft_printf(char const *form, ...)
{
	char	out[FT_PRINTF_MAXL];
	va_list	args;
	int		printedc;

	va_start(args, form);
	printedc = sprintf_wrapper(out, form, args);
	va_end(args);
	if (printedc >= 0)
		write(1, out, printedc);
	return (printedc);
}
