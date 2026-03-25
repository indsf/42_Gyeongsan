/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:05:49 by inhlee            #+#    #+#             */
/*   Updated: 2025/06/14 21:45:11 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_len(const char *input, va_list ap)
{
	int	len;

	len = 0;
	if (*input == 'c')
		len += ft_char((char)va_arg(ap, int));
	if (*input == 's')
		len += ft_str(va_arg(ap, char *));
	if (*input == 'd' || *input == 'i')
		len += ft_int(va_arg(ap, int));
	if (*input == 'p')
		len += ft_pointer((unsigned long)va_arg(ap, void *), 87);
	if (*input == 'u')
		len += ft_unsigned(va_arg(ap, unsigned int));
	if (*input == 'x')
		len += ft_hex(va_arg(ap, unsigned int), 87);
	if (*input == 'X')
		len += ft_hex(va_arg(ap, unsigned int), 55);
	if (*input == '%')
		len += ft_char('%');
	return (len);
}

int	ft_printf(const char *input_argv, ...)
{
	int		len_count;
	va_list	ap;

	len_count = 0;
	va_start(ap, input_argv);
	while (*input_argv != 0)
	{
		if (*(input_argv++) == '%')
		{
			if (ft_strchr("cspdiuxX%", *input_argv) && *input_argv != 0)
				len_count += ft_print_len(input_argv, ap);
			else if (*(input_argv--) == '\0')
				len_count = -1;
			else
				len_count += ft_char('%');
			input_argv++;
		}
		else
			len_count += ft_char(*(input_argv - 1));
	}
	va_end(ap);
	return (len_count);
}
