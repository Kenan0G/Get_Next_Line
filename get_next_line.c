/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:54:08 by kgezgin           #+#    #+#             */
/*   Updated: 2022/12/12 17:36:50 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	*ft_delete(char *temp)
{
	int		i;
	int		j;
	char	*str;

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

	if (!*gnl)
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

void	*ft_free(char *gnl, char *temp)
{
	if (gnl)
		free(gnl);
	free(temp);
	return (NULL);
}

char	*ft_write(long len, char *temp, char *gnl, int fd)
{
	if (BUFFER_SIZE < 1)
		return (NULL);
	len = read(fd, temp, BUFFER_SIZE);
	if (len < 0)
	{
		free(temp);
		free(gnl);
		return (NULL);
	}
	temp[len] = '\0';
	gnl = ft_strjoin(gnl, temp);
	return (gnl);
}

char	*get_next_line(int fd)
{
	static char	*gnl;
	char		*temp;
	char		*res;
	long		len;

	if (read(fd, NULL, 0) < 0 || BUFFER_SIZE < 1)
		return (NULL);
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	len = 1;
	while (len && !ft_strchr(gnl, '\n'))
	{
		gnl = ft_write(len, temp, gnl, fd);
		if (BUFFER_SIZE > (int)ft_strlen(temp))
			break ;
	}
	if (!gnl)
		ft_free(gnl, temp);
	res = ft_res(gnl);
	gnl = ft_delete(gnl);
	free(temp);
	return (res);
}
/*
int main(void)
{
    int        fd;
    char    *str;

	fd = open("text.txt", O_RDONLY);
    str = get_next_line(fd);
	printf("%s", str);
    free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);

    close(fd);
	return (0);
}
*/
