/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:23:18 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 13:30:07 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*placeholder;

	placeholder = (unsigned char *)s;
	while (n > 0)
	{
		*placeholder = (unsigned char)c;
		placeholder++;
		n--;
	}
	return (s);
}
