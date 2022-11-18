/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouchar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:19:58 by rbouchar          #+#    #+#             */
/*   Updated: 2022/11/18 17:06:21 by rbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c && s[i] != '\0')
		i++;
	if (s[i] == (char)c)
		return ((char *)(s + i));
	else
		return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = s;
	i = 0;
	while (i < n)
		ptr[i++] = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (count * size));
	return (ptr);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *line, char *buffer)
{
	char	*result;
	int		i;
	int		k;

	i = ft_strlen(line);
	k = ft_strlen(buffer);
	result = ft_calloc((i + k + 1), sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	k = 0;
	while (line[i] != '\0')
		result[k++] = line[i++];
	i = 0;
	while (buffer[i] != '\0')
		result[k++] = buffer[i++];
	free(line);
	return (result);
}
