/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-nada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 22:45:05 by ede-nada          #+#    #+#             */
/*   Updated: 2020/10/12 12:10:22 by ede-nada         ###   ########.fr       */
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

static int	new_line(char *str)
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

static int	return_line(char **line, char **remain, int ret)
{
	int		nl;
	char	*tmp;

	if (ret < 0)
		return (-1);
	if (!(*remain) && !ret)
	{
		*line = ft_strdup("");
		free_line(remain);
		return (0);
	}
	nl = new_line(*remain);
	if (nl >= 0)
	{
		*line = ft_substr(*remain, 0, nl);
		tmp = ft_substr(*remain, nl + 1, ft_strlen(*remain) - nl);
		free(*remain);
		*remain = tmp;
		tmp = NULL;
		return (1);
	}
	*line = ft_substr(*remain, 0, ft_strlen(*remain));
	free_line(remain);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*remain;
	char		*buffer;
	char		*tmp;
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (!(buffer = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	if (!remain)
		remain = ft_strdup("");
	while (new_line(remain) == -1 && (ret = read(fd, buffer, BUFFER_SIZE)))
	{
		if (ret < 0)
		{
			free(buffer);
			return (-1);
		}
		buffer[ret] = '\0';
		tmp = ft_strjoin(remain, buffer);
		free_line(&remain);
		remain = tmp;
	}
	free(buffer);
	return (return_line(line, &remain, ret));
}
