/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:14:27 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 17:47:50 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(const char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_putstr_fd(const char *s, int fd, char *arg)
{
	while (*s)
		write(fd, s++, 1);
	if (arg)
	{
		while (*arg)
			write(fd, arg++, 1);
	}
}
