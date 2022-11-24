/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouchar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:56 by rbouchar          #+#    #+#             */
/*   Updated: 2022/11/24 15:42:46 by rbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*ft_nextline(char *line, char *result)
{
	char	*nextline;
	int		sizenline;
	int		i;

	i = 0;
	if (!result)
		return (NULL);
	sizenline = ft_strlen(line) - ft_strlen(result);
	if (sizenline == 0)
	{
		free(line);
		return (NULL);
	}
	nextline = ft_calloc(sizenline + 1, sizeof(char));
	if (!nextline)
		return (NULL);
	while (line[ft_strlen(result) + i] != '\0')
	{
		nextline[i] = line[ft_strlen(result) + i];
		i++;
	}
	free(line);
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
	{
		free(line);
		return (NULL);
	}
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
	if (!line)
		free(buf);
	if (!line)
		return (NULL);
	ret = 1;
	while (ret > 0 && ft_strchr(line, 10) == NULL)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0 || (ret == 0 && line[0] == '\0'))
		{
			free(buf);
			free(line);
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
	static char	*line[OPEN_MAX];
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(line[fd]);
		line[fd] = NULL;
		return (NULL);
	}
	line[fd] = ft_read(line[fd], fd);
	if (line[fd] == NULL)
		return (NULL);
	result = ft_result(line[fd]);
	if (result == NULL)
	{
		free(line[fd]);
		line[fd] = NULL;
		return (NULL);
	}
	line[fd] = ft_nextline(line[fd], result);
	return (result);
}
/*
int	main(void)
{
	int	fd1;
	int	fd2;
	int	fd3;
	int	fd4;
	int	fd5;
	char	*line;

	fd1 = open("text9", O_RDONLY);
	fd2 = open("text10", O_RDONLY);
	fd3 = open("text11", O_RDONLY);
	fd4 = open("text12", O_RDONLY);
	fd5 = open("text13", O_RDONLY);

	line = get_next_line(fd1);

	while (line)
	{

		printf("RESULT fd1: %s\n", line);
		free(line);

		line = get_next_line(fd2);
		printf("RESULT fd2: %s\n", line);
		free(line);

		line = get_next_line(fd3);
		printf("RESULT fd3: %s\n", line);
		free(line);

		line = get_next_line(fd4);
		printf("RESULT fd4: %s\n", line);
		free(line);

		line = get_next_line(fd5);
		printf("RESULT fd5: %s\n", line);
		free(line);

		printf("\n-----------------------------\n");

		line = get_next_line(fd1);
	}
	return (0);
}
*/
