/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:05:32 by arocca            #+#    #+#             */
/*   Updated: 2025/09/24 17:14:06 by arocca           ###   ########.fr       */
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

bool	err_errno(char *msg)
{
	if (!msg || !*msg)
		msg = "errno";
	ft_printf(ERRNOLOG, msg, strerror(errno));
	return (false);
}

void	debug(char *message)
{
	ft_printf("\e[1;31m📛 DEBUG - %s 📛\e[0m\n", message);
}
