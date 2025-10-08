/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:05:32 by arocca            #+#    #+#             */
/*   Updated: 2025/10/08 09:14:39 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <errno.h>
#include "ft_printf.h"

bool	err(char *msg)
{
	if (msg && *msg)
		ft_printf("%s%s%s", ERROR, msg, EOL);
	return (false);
}

bool	err_str(char *msg, char *str)
{
	if (!msg || !str || !*msg || !*str)
		return (false);
	if (str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';
	ft_printf(ERROR);
	ft_printf(msg, str);
	ft_printf(EOL);
	return (false);
}

bool	err_errno(char *msg, char *custom_err, bool exit_err)
{
	if (!msg || !*msg)
		msg = "errno";
	if (!custom_err || !*custom_err)
		custom_err = strerror(errno);
	if (exit_err)
	{
		ft_printf(ERROR);
		ft_printf("%s: %s", msg, custom_err);
		ft_printf(EOL);
	}
	else
		ft_printf(ERRNOLOG, msg, custom_err);
	return (false);
}
