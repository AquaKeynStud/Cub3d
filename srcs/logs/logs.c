/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:08:07 by arocca            #+#    #+#             */
/*   Updated: 2025/10/08 11:46:46 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "ft_printf.h"

void	print_header(void)
{
	ft_printf("\n\e[1;107;38;5;140m");
	ft_printf("\t╭━━━━━━━━━════════╕ ❖ CUB3D ❖ ╒════════━━━━━━━━━╮");
	ft_printf("\e[0m\n\e[1;107;38;5;140m");
	ft_printf("\t│%5c⛲ • Welcome to cub3d by Keyn 🫧 • 🎍%5c│", ' ', ' ');
	ft_printf("\e[0m\n\e[1;107;38;5;140m");
	ft_printf("\t╰━━━━━━━━━══════╛ 🍂 光 • 線 🪼 ╘══════━━━━━━━━━╯");
	ft_printf("\e[0m\n\n");
}

bool	info(char *message, char *format, char *str)
{
	if (!message || !*message)
		return (true);
	if (!str || !*str)
		ft_printf(message, format, EOL);
	else
		ft_printf(message, format, str, EOL);
	return (true);
}
