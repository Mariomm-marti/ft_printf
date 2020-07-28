/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 23:54:27 by mmartin-          #+#    #+#             */
/*   Updated: 2020/07/28 15:59:17 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "libft/includes/libft.h"

/*
**	DESCRIPTION
**		Given the arguments that should be considered for specifier c,
**		write into _out_ the result
**	RETURN VALUES
**		Returns the number of characters sent to _out_
*/

int		char_handle(char *out, t_flag const *flag, char const chr)
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
**	DESCRIPTION
**		Given the arguments that should be considered for specifier s,
**		write into _out_ the result
**	RETURN VALUES
**		Returns the number of characters sent to _out_
*/

int		string_handle(char *out, t_flag const *flag, char const *str)
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
