/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 02:13:08 by mmartin-          #+#    #+#             */
/*   Updated: 2020/07/28 00:27:55 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "libft/includes/libft.h"

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
