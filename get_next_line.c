/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-nada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 22:45:05 by ede-nada          #+#    #+#             */
/*   Updated: 2020/10/12 17:33:33 by ede-nada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static int	return_line(char **line, char **remainder, int ret)
{
	int		nl;
	char	*tmp;

	if (ret < 0)
		return (-1);
	if (!(*remainder) && !ret)
	{
		*line = ft_strdup("");
		free_line(remainder);
		return (0);
	}
	nl = is_newline(*remainder);
	if (nl >= 0)
	{
		*line = ft_substr(*remainder, 0, nl);
		tmp = ft_substr(*remainder, nl + 1, ft_strlen(*remainder) - nl);
		free(*remainder);
		*remainder = tmp;
		if (*remainder && (*remainder)[0] == '\0')
			free_line(remainder);
		return (1);
	}
	*line = ft_substr(*remainder, 0, ft_strlen(*remainder));
	free_line(remainder);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*remainder;
	char		*buffer;
	char		*tmp;
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE < 1 ||
	!(buffer = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	if (!remainder)
		remainder = ft_strdup("");
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		tmp = ft_strjoin(remainder, buffer);
		free_line(&remainder);
		remainder = tmp;
		if (is_newline(remainder) != -1)
			break ;
	}
	free_line(&buffer);
	return (return_line(line, &remainder, ret));
}
