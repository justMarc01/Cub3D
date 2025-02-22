/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:07:07 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/14 18:27:05 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}

char	*ft_strncpy_gnl(char *dest, const char *src, size_t n)
{
	size_t	index;

	index = 0;
	while ((src[index] != '\0') && (index < n))
	{
		dest[index] = src[index];
		index++;
	}
	while (index < n)
	{
		dest[index] = '\0';
		index++;
	}
	return (dest);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	size_t	index;
	char	*first_occ;

	if (s == NULL)
		return (NULL);
	index = 0;
	first_occ = NULL;
	while (s[index] != '\0')
	{
		if (s[index] == (unsigned char)c)
		{
			first_occ = (char *)&s[index];
			return (first_occ);
		}
		index++;
	}
	if ((unsigned char)c == '\0')
	{
		first_occ = (char *)&s[index];
	}
	return (first_occ);
}

char	*ft_strdup_gnl(const char *s)
{
	size_t	index;
	char	*new_string;

	new_string = malloc(ft_strlen_gnl(s) + 1);
	index = 0;
	if (new_string == NULL)
	{
		return (NULL);
	}
	while (s[index])
	{
		new_string[index] = s[index];
		index++;
	}
	new_string[index] = '\0';
	return (new_string);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		new_index;
	int		index;
	char	*new;

	if (s1 == NULL)
		s1 = ft_strdup_gnl("");
	new = malloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	new_index = 0;
	index = 0;
	while (s1[index])
	{
		new[new_index++] = s1[index++];
	}
	index = 0;
	while (s2[index])
	{
		new[new_index++] = s2[index++];
	}
	new[new_index] = '\0';
	free((char *)s1);
	return (new);
}
