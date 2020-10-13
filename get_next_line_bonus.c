/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-nada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 19:17:14 by ede-nada          #+#    #+#             */
/*   Updated: 2020/10/12 20:35:04 by ede-nada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	free_line(char **str)
{
	if (!(*str))
		return ;
	free(*str);
	*str = NULL;
}

static int	is_newline(char *str)
{
	int i;

	if (!(str))
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int	return_line(char **line, char **remainder, int ret, int fd)
{
	int		nl;
	char	*tmp;

	if (ret < 0)
		return (-1);
	if (!(remainder[fd]) && !ret)
	{
		*line = ft_strdup("");
		free_line(&remainder[fd]);
		return (0);
	}
	nl = is_newline(remainder[fd]);
	if (nl >= 0)
	{
		*line = ft_substr(remainder[fd], 0, nl);
		tmp = ft_substr(remainder[fd], nl + 1, ft_strlen(remainder[fd]) - nl);
		free(remainder[fd]);
		remainder[fd] = tmp;
		if (remainder[fd] && (remainder[fd][0] == '\0'))
			free_line(&remainder[fd]);
		return (1);
	}
	*line = ft_substr(remainder[fd], 0, ft_strlen(remainder[fd]));
	free_line(&remainder[fd]);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*remainder[OPEN_MAX];
	char		*buffer;
	char		*tmp;
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE < 1 ||
	!(buffer = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	if (!remainder[fd])
		remainder[fd] = ft_strdup("");
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		tmp = ft_strjoin(remainder[fd], buffer);
		free_line(&remainder[fd]);
		remainder[fd] = tmp;
		if (is_newline(remainder[fd]) != -1)
			break ;
	}
	free_line(&buffer);
	return (return_line(line, remainder, ret, fd));
}
