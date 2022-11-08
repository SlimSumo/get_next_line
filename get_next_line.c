/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouchar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:56 by rbouchar          #+#    #+#             */
/*   Updated: 2022/11/08 22:35:17 by rbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft/libft.h"
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 6
#endif

char	*ft_cpy_to_temp(char *buf, char *temp, int readsize)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (temp)
	{
		while (temp[j])
			j++;
	}
	while (i < readsize)
		temp[j++] = buf[i++];
	temp[j] ='\0';
	return (temp);
}

void	ft_cor_temp(char *temp, int i)
{
	int	k;

	k = 0;
	i++;
	if (i != 0)
	{
		while (temp[i])
			temp[k++] = temp[i++];
	}
	temp[k] = '\0';
}

char	*ft_cpy_temp_to_line(char *temp, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	line = malloc((ft_strlen(temp)) * sizeof(char));
	if (line == NULL)
		return (NULL);
	while (temp[i] != '\n')
		line[j++] = temp[i++];
	ft_cor_temp(temp, i);
	if (temp[i] == '\0')
		line[j] = '\0';
	else
		line[j] = '\n';
	return (line);
}

char	*ft_realloc(char *temp, int k)
{
	char	*newptr;

	if (!temp)
	{
		newptr = malloc((k + 1) * sizeof(char));
		if (newptr == NULL)
			return (NULL);
	}
	else
	{
		newptr = malloc((k + 1) * sizeof(char));
		if (newptr == NULL)
			return (NULL);
		ft_memcpy(newptr, temp, k);
		temp = newptr;
	}
	return (newptr);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*temp;
	static int	k;
	static int	flag;
	char		*line;
	int			readsize;

	if (flag == 1)
		return (NULL);
	if (flag != 1)
	{
		while ((readsize = read(fd, buf, BUFFER_SIZE)) > 0)
		{
			k += readsize;
			temp = ft_realloc(temp, k);
			ft_cpy_to_temp(buf, temp, readsize);
		}
		line = ft_cpy_temp_to_line(temp, line);
	}
	if (temp[0] == '\0')
		flag = 1;
	return (line);
}

int main()
{
	int	fd;
	int nbl = 50;

	fd = open("text", O_RDONLY);
	while (nbl > 0)
	{
		printf("Resultat %s", get_next_line(fd));
		nbl--;
	}
	return (0);
}
