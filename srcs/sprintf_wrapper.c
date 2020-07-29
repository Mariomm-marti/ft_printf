/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf_wrapper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 23:49:41 by mmartin-          #+#    #+#             */
/*   Updated: 2020/07/29 17:46:22 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "libft/includes/libft.h"

/*
**	Mainly used for precision flag management, counts the number of zeros
**	that should be skipped (as in '%.00009d')
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
**	Handles argument parsed width and precision
*/

static int	arg_handle(char const *form, va_list args, t_flag *flag)
{
	if (*form == '*' && *(form - 1) == '.')
	{
		flag->prec = va_arg(args, int);
		flag->left = flag->prec < 0 && !flag->left ? 0 : flag->left;
		flag->prec = flag->prec < 0 ? -1 : flag->prec;
	}
	else if (*form == '*' && (flag->width = va_arg(args, int)) < 0)
	{
		flag->left = 1;
		flag->width = -flag->width;
		flag->zero = 0;
	}
	return (0);
}

/*
**	Selects individual characters and apply filters so the flags are triggered
*/

static int	flag_handle(char const *form, t_flag *flag)
{
	if (ft_isdigit(*form) && *(form - 1) == '.')
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
**	DESCRIPTION
**		Heart of the printf, manages all logic.
**		Analyzes format used, manage all flags and specifiers, and ensures
**		segmentation faults cannot happen
**	RETURN VALUES
**		Returns the number of characters sent to _out_
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
		else if (*form == '*')
			form += arg_handle(form, args, &flag);
		else if (ft_strchr("- +.#0123456789", *form))
			form += flag_handle(form, &flag);
		else if (!(is_flag = 0))
			printc += type_handle(out + printc, *form, args, &flag);
		form++;
	}
	*(out + printc) = 0;
	return (printc);
}
