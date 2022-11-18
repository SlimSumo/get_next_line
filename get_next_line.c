/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouchar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:56 by rbouchar          #+#    #+#             */
/*   Updated: 2022/11/18 17:11:06 by rbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	ft_size_nextline(char *line)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (line [i] != '\n')
		i++;
	i++;
	while (line[i] != '\0')
	{
		i++;
		k++;
	}
	return (k + 1);
}

char	*ft_nextline(char *line)
{
	char	*nextline;
	int		sizenline;
	int		i;
	int		k;

	i = 0;
	k = 0;
	sizenline = ft_size_nextline(line);
	if (sizenline == 0)
		return (NULL);
	nextline = ft_calloc(sizenline + 1, sizeof(char));
	if (line)
	{	
		while (line[i] != '\n' && line[i] != '\0')
			i++;
		i++;
	}
	while (line[i] != '\0')
		nextline[k++] = line[i++];
	return (nextline);
}

char	*ft_result(char	*line)

{
	char	*result;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	result = ft_calloc((i + 1), sizeof(char));
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		result[i] = line[i];
		i++;
	}
	result[i] = line[i];
	return (result);
}

char	*ft_read(char *line, int fd)
{
	char	*buf;
	int		ret;

	buf = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!line)
		line = ft_calloc(1, 1);
	ret = 1;
	while (ret > 0 && ft_strchr(line, '\n') == NULL)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == 0)
			return (NULL);
		line = ft_strjoin(line, buf);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = ft_read(line, fd);
	if (line == NULL)
	{
		free(line);
		return (NULL);
	}
	result = ft_result(line);
	line = ft_nextline(line);
	return (result);
}

int main()
{
	int	fd;
	int nbl = 5;

	fd = open("text_vide", O_RDONLY);
	while (nbl > 0)
	{
		printf("Resultat %s", get_next_line(fd));
		nbl--;
	}
	return (0);
}

