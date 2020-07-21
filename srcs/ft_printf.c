/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 02:13:08 by mmartin-          #+#    #+#             */
/*   Updated: 2020/07/21 23:13:17 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "libft/includes/libft.h"

/*
** Converts ptr literal integer _num_ to it HEX value
*/

static int	convert_addr(char *out, unsigned long int num)
{
	unsigned int const	conv_length = ft_logn(16, num);

	if (num == 0 && (*out = '0'))
		return (1);
	while (num > 0)
	{
		*(out-- + conv_length) = "0123456789abcdef"[num % 16];
		num /= 16;
	}
	return (conv_length + 1);
}

/*
** Handles requests for format %c with it respective flags
*/

static int	char_handle(char *out, t_flag const *flag, char const chr)
{
	int	sent;

	sent = 0;
	while ((!flag->left || flag->zero) && sent < flag->width - 1)
		*(out + sent++) = flag->zero ? '0' : ' ';
	*(out + sent++) = chr;
	while (sent < flag->width)
		*(out + sent++) = ' ';
	return (sent);
}

/*
** Handles requests for format %s with it respective flags
*/

static int	string_handle(char *out, t_flag const *flag, char const *str)
{
	int	sent;
	int	strptr;
	int	prec_length;

	sent = 0;
	if (!str)
		str = "(null)";
	prec_length = ft_strlen(str);
	if (flag->prec >= 0)
		prec_length = flag->prec > prec_length ? prec_length : flag->prec;
	while (!flag->left && sent < flag->width - prec_length)
		*(out + sent++) = flag->zero ? '0' : ' ';
	strptr = 0;
	while (*(str + strptr) && strptr < prec_length)
		*(out + sent++) = *(str + strptr++);
	while (flag->left && sent < flag->width)
		*(out + sent++) = ' ';
	return (sent);
}

/*
** Handles requests for format %s with it respective flags
*/

static int	ptr_handle(char *out, t_flag *flag, void *ptr)
{
	int		sent;
	int		sentptr;

	sent = 0;
	if (flag->zero && flag->prec < 0)
		flag->prec = flag->width - 2;
	while (!flag->left &&
			sent < flag->width - 14 - (flag->prec >= 13 ? flag->prec - 12 : 0))
		*(out + sent++) = ' ';
	*(out + sent++) = '0';
	*(out + sent++) = 'x';
	sentptr = -1;
	while (++sentptr < (flag->prec > 12 ? flag->prec - 12 : 0))
		*(out + sent++) = '0';
	sent += convert_addr(out + sent, (unsigned long int)ptr);
	while (flag->left && sent < flag->width)
		*(out + sent++) = ' ';
	return (sent);
}

/*
**	Selects individual characters and apply filters so the flags are triggered
*/

static int	flag_handle(char const *form, va_list args, t_flag *flag)
{
	if (*form == '*' && *(form - 1) == '.')
	{
		flag->prec = va_arg(args, int);
		flag->prec = flag->prec < 0 ? -flag->prec : flag->prec;
	}
	else if (*form == '*' && (flag->width = va_arg(args, int)) < 0)
	{
		flag->left = 1;
		flag->width = -flag->width;
	}
	else if (*form >= '0' && *form <= '9' && *(form - 1) == '.')
		return (ft_countdigits(flag->prec = ft_atoi(form)) - 1);
	else if (*form >= '1' && *form <= '9')
		return (ft_countdigits(flag->width = ft_atoi(form)) - 1);
	else if (*form == '-' && !(flag->zero = 0))
		flag->left = 1;
	else if (*form == '+' && !(flag->space = 0))
		flag->plus = 1;
	else if (*form == '.')
		flag->prec = 0;
	flag->sharp = *form == '#' ? 1 : flag->sharp;
	flag->zero = *form == '0' && !flag->left ? 1 : flag->zero;
	flag->space = *form == ' ' && !flag->plus ? 1 : flag->space;
	return (0);
}

/*
**	Handles requests for flag ending and writing result out
*/

static int	type_handle(char *out, char const type, va_list args, t_flag *flag)
{
	if (type == 'c')
		return (char_handle(out, flag, va_arg(args, int)));
	if (type == 's')
		return (string_handle(out, flag, va_arg(args, char const*)));
	if (type == 'p')
		return (ptr_handle(out, flag, va_arg(args, void *)));
	return (-FT_PRINTF_MAXL);
}

/*
**	Creates a workflow for _form_ analyzing. To diagnose errors it will
**	return a negative number
*/

static int	sprintf_wrapper(char *out, char const *form, va_list args)
{
	register int			printc;
	register unsigned char	is_flag;
	t_flag					flag;

	printc = 0;
	is_flag = 0;
	while (*form && printc >= 0)
	{
		if (*form == '%' && !is_flag && (is_flag = 1))
		{
			ft_bzero(&flag, sizeof(t_flag));
			flag.prec = -1;
		}
		else if (!is_flag)
			*(out + printc++) = *form;
		else if (ft_strchr("*- +.#0123456789", *form))
			form += flag_handle(form, args, &flag);
		else if ((printc += type_handle(out + printc, *form, args, &flag)))
			is_flag = 0;
		form++;
	}
	*(out + printc) = 0;
	return (printc);
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
