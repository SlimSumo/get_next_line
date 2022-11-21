/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouchar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:19:58 by rbouchar          #+#    #+#             */
/*   Updated: 2022/11/21 17:30:35 by rbouchar         ###   ########.fr       */
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
		ptr[i++] = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count);
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

char	*ft_strjoin(char *line, char *buffer, int ret)
{
	char	*result;
	int		i;
	int		k;


	if (!line || !buffer)
		return (NULL);
	i = ft_strlen(line);
	result = ft_calloc((i + ret + 1), sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	k = 0;
	while (line[i] != '\0')
		result[k++] = line[i++];
	i = 0;
	if (ret > 0)
		while (buffer[i] != '\0' && i < ret)
			result[k++] = buffer[i++];
	free(line);
	return (result);
}
