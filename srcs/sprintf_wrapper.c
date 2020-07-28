/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf_wrapper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 23:49:41 by mmartin-          #+#    #+#             */
/*   Updated: 2020/07/28 03:24:55 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "libft/includes/libft.h"

/*
**	Mainly used for precision flag management, counts the number of zeros
**	that should be skipped
*/

static int	zeroes(char const *in)
{
	unsigned int	count;

	count = 0;
	while (*(in + count) == '0' && ft_isdigit(*(in + count + 1)))
		count++;
	return (count);
}

/*
**	Selects individual characters and apply filters so the flags are triggered
*/

static int	flag_handle(char const *form, va_list args, t_flag *flag)
{
	if (*form == '*' && *(form - 1) == '.')
	{
		flag->prec = va_arg(args, int);
		flag->left = flag->prec < 0 ? 1 : flag->left;
		flag->prec = flag->prec < 0 ? 0 : flag->prec;
	}
	else if (*form == '*' && (flag->width = va_arg(args, int)) < 0)
	{
		flag->left = 1;
		flag->width = -flag->width;
	}
	else if (ft_isdigit(*form) && *(form - 1) == '.')
		return (ft_countdigits(flag->prec = ft_atoi(form)) + zeroes(form) - 1);
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
	if (type == 'd' || type == 'i')
		return (int_handle(out, flag, va_arg(args, int)));
	if (type == 'u')
		return (uint_handle(out, flag, va_arg(args, unsigned int)));
	if (type == 'x')
		return (hex_handle(out, flag, va_arg(args, unsigned int), FT_PRINTF_L));
	if (type == 'X')
		return (hex_handle(out, flag, va_arg(args, unsigned int), FT_PRINTF_U));
	if (type == '%')
		return (char_handle(out, flag, '%'));
	return (-FT_PRINTF_MAXL);
}

/*
**	TODO: Redo comment (sprintf_wrapper#sprintf_wrapper)
*/

int			sprintf_wrapper(char *out, char const *form, va_list args)
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
		else if (!(is_flag = 0))
			printc += type_handle(out + printc, *form, args, &flag);
		form++;
	}
	*(out + printc) = 0;
	return (printc);
}
