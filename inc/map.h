/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:54:57 by arocca            #+#    #+#             */
/*   Updated: 2025/09/18 17:43:17 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* -- Includes -- */

/* -- Structures -- */
typedef struct s_image
{
	void	*f;
	void	*c;
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
}			t_image;

typedef struct s_map
{
	int	fd;
}			t_map;

#endif