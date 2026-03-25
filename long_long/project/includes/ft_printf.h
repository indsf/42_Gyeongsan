/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 09:06:52 by inhlee            #+#    #+#             */
/*   Updated: 2025/08/16 19:18:41 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int	ft_char(int c);
int	ft_str(char *s);
int	ft_int(int num);
int	ft_unsigned(unsigned int num);
int	ft_pointer(unsigned long adr, int asc);
int	ft_hex(unsigned int hex, int asc);
int	ft_printf(const char *input_argv, ...);

#endif
