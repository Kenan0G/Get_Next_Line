/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:17:06 by kgezgin           #+#    #+#             */
/*   Updated: 2022/12/16 17:17:17 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	*ft_delete(char *temp)
{
	int		i;
	int		j;
	char	*str;

	if (!temp)
		return (NULL);
	i = 0;
	j = 0;
	str = NULL;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i])
	{
		str = malloc(sizeof(char) * (ft_strlen(temp) - i + 1));
		if (!str)
			return (NULL);
		if (temp[i] == '\n')
			i++;
		while (temp[i] != '\0')
			str[j++] = temp[i++];
		str[j] = '\0';
	}
	free(temp);
	return (str);
}

char	*ft_res(char *gnl)
{
	char	*res;
	int		i;
	int		j;

	if (!gnl || !*gnl)
		return (NULL);
	i = 0;
	while (gnl[i] && gnl[i] != '\n')
		i++;
	if (gnl[i] == '\n')
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (j < i)
	{
		res[j] = gnl[j];
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_write(long len, char *temp, char *gnl, int fd)
{
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	len = read(fd, temp, BUFFER_SIZE);
	if (len < 0)
		return (NULL);
	temp[len] = '\0';
	gnl = ft_strjoin(gnl, temp);
	return (gnl);
}

char	*get_next_line(int fd)
{
	static char	*gnl[1024];
	char		*temp;
	char		*res;
	long		len;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	len = 1;
	while (len && !ft_strchr(gnl[fd], '\n'))
	{
		gnl[fd] = ft_write(len, temp, gnl[fd], fd);
		if (!gnl[fd] || BUFFER_SIZE > (int)ft_strlen(temp))
			break ;
	}
	res = ft_res(gnl[fd]);
	gnl[fd] = ft_delete(gnl[fd]);
	if (temp)
		free(temp);
	return (res);
}
