/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouchar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:56 by rbouchar          #+#    #+#             */
/*   Updated: 2022/11/21 17:30:31 by rbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_nextline(char *line, char *result)
{
	char	*nextline;
	int		sizenline;
	int		i;

	i = 0;
	if (!result)
		return(NULL);
	sizenline = ft_strlen(line) - ft_strlen(result);
	if (sizenline == 0)
		return (NULL);
	nextline = ft_calloc(sizenline + 1, sizeof(char));
	if (!nextline)
		return (NULL);
	while (line[ft_strlen(result) + i] != '\0')
	{
		nextline[i] = line[ft_strlen(result) + i];
		i++;
	}
	return (nextline);
}

char	*ft_result(char	*line)

{
	char	*result;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		i++;
	result = ft_calloc((i + 1), sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		result[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		result[i] = line[i];
	return (result);
}

char	*ft_read(char *line, int fd)
{
	char	*buf;
	int		ret;

	buf = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!line)
		line = ft_calloc(1, sizeof(char));
	ret = 1;
	while (ret > 0 && ft_strchr(line, 10) == NULL)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
		{
			free(buf);
			free(line);
			return (NULL);
		}
		if (ret == 0 && line[0] == '\0')
		{
			free(line);
			free(buf);
			return (NULL);
		}
		buf[ret] = '\0';
		line = ft_strjoin(line, buf, ret);
	}
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	line = ft_read(line, fd);
	if (line == NULL)
		return (NULL);
	result = ft_result(line);
	line = ft_nextline(line, result);
	return (result);
}
/*
int main()
{
	int	fd;
	int nbl = 18;

	fd = open("text_vide", O_RDONLY);
	while (nbl > 0)
	{
		printf("Resultat: %s |", get_next_line(fd));
		nbl--;
	}
	return (0);
}
*/
